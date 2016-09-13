#ifndef TREE_HPP
#define TREE_HPP

#include "utils.hpp"

BEGIN_NAMESPACE_UTILS

template<class T> class Tree
{
public:
    typedef typename T::value_type value_type;
    typedef typename T::parameter_value_type parameter_value_type;
    typedef typename T::node_type node_type;
    typedef typename T::node_iterator node_iterator;
    typedef typename T::node_const_iterator node_const_iterator;

    Tree() = default;
    Tree(const Tree&) = delete;
    Tree(Tree&&) = delete;

    void addNode(parameter_value_type value, node_type parent = node_type())
    {
        m_tree.addNode(value, parent);
    }

    std::size_t nbRoots() const
    {
        return m_tree.nbRoots();
    }

    std::pair<node_iterator, node_iterator> children()
    {

    }

private:
    T m_tree;
};

END_NAMESPACE_UTILS

#endif // TREE_HPP
