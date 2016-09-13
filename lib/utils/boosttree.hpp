#ifndef BOOSTTREE_HPP
#define BOOSTTREE_HPP

#include "utils/parametertrait.hpp"

#include <boost/graph/adjacency_list.hpp>

BEGIN_NAMESPACE_UTILS

template<class T> class BoostTree
{
public:
    typedef T Noeud;
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::bidirectionalS, Noeud> graph_type;
    typedef typename boost::graph_traits<graph_type>::vertex_descriptor vertex_descriptor;
    typedef typename boost::graph_traits<graph_type>::vertex_iterator vertex_iterator;
    typedef std::pair<vertex_iterator, vertex_iterator> type_pair_vertex_iterator;
    typedef std::list<vertex_descriptor> list_vertex_descriptor;

    BoostTree() = default;

    vertex_descriptor addNode(typename utils::const_parameter_trait<T>::type node)
    {
        vertex_descriptor v = add_vertex(m_graph);
        m_graph[v] = node;
        m_roots.push_back(v);
        return v;
    }

//    vertex_descriptor addNode(T&& node)
//    {
//        vertex_descriptor v = add_vertex(m_graph);
//        m_graph[v] = std::move(node);
//        m_roots.push_back(v);
//        return v;
//    }

    vertex_descriptor addNode(typename utils::const_parameter_trait<T>::type node, vertex_descriptor parent)
    {
        vertex_descriptor v = add_vertex(m_graph);
        m_graph[v] = node;
        boost::add_edge(parent, v, m_graph);
        return v;
    }

//    vertex_descriptor addNode(T&& node, vertex_descriptor parent)
//    {
//        vertex_descriptor v = add_vertex(m_graph);
//        m_graph[v] = std::move(node);
//        boost::add_edge(parent, v, m_graph);
//        return v;
//    }

    typename utils::const_parameter_trait<T>::type operator()(vertex_descriptor v) const
    {
        return m_graph[v];
    }

    const list_vertex_descriptor& roots() const
    {
        return m_roots;
    }

    std::size_t nbRoots() const
    {
        return m_roots.size();
    }

    vertex_descriptor parent(vertex_descriptor v) const
    {
        typename graph_type::inv_adjacency_iterator i, i_end;
        boost::tie(i, i_end) = boost::inv_adjacent_vertices(v, m_graph);
        assert(std::distance(i, i_end) == 1);
        return *i;
    }

    list_vertex_descriptor children(vertex_descriptor v) const
    {
        typename boost::graph_traits<graph_type>::adjacency_iterator i, i_end;
        boost::tie(i, i_end) = boost::adjacent_vertices(v, m_graph);
        list_vertex_descriptor res;
        std::copy(i, i_end, std::back_inserter(res));
        return res;
    }

    vertex_descriptor child(vertex_descriptor v, std::size_t pos) const
    {
        assert(pos < nbChildren(v));
        typename boost::graph_traits<graph_type>::adjacency_iterator i, i_end;
        boost::tie(i, i_end) = boost::adjacent_vertices(v, m_graph);
        std::advance(i, pos);
        return *i;
    }

    std::size_t nbChildren(vertex_descriptor v) const
    {
        typename boost::graph_traits<graph_type>::adjacency_iterator i, i_end;
        boost::tie(i, i_end) = boost::adjacent_vertices(v, m_graph);
        return std::distance(i, i_end);
    }

    std::size_t positionFromParent(vertex_descriptor v) const
    {
        vertex_descriptor p = parent(v);
        list_vertex_descriptor ch = children(p);
        assert(!ch.empty());
        typename list_vertex_descriptor::const_iterator i = std::find(ch.cbegin(), ch.cend(), v);
        assert(i != ch.end());
        return std::distance(ch.cbegin(), i);
    }

private:
    graph_type m_graph;
    list_vertex_descriptor m_roots;
};

END_NAMESPACE_UTILS

#endif // BOOSTTREE_HPP
