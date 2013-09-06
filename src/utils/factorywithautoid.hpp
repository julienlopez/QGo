#ifndef FACTORYWITHAUTOID_HPP
#define FACTORYWITHAUTOID_HPP

#include <utils/singleton.hpp>
#include <utils/defaultfactoryerrorpolicy.hpp>
#include <utils/defaultfactorystoragepolicies.hpp>

#include <functional>
#include <cassert>
#include <limits>

BEGIN_NAMESPACE_UTILS

template<class AbstractProduct, class IdentifierType>
struct trait_max_value
{
    static IdentifierType value()
    {
        return std::numeric_limits<IdentifierType>::max();
    }
};

template<	class AbstractProduct,
            class IdentifierType = std::size_t,
            template<class, class, class> class Storage = SimpleVectorStorage,
            class ProductCreator = std::function<AbstractProduct*()>,
            template<class, class> class FactoryErrorPolicy = DefaultFactoryErrorPolicy
            >
class FactoryWithAutoId :   public FactoryErrorPolicy<IdentifierType, AbstractProduct>,
                            protected Storage<IdentifierType, AbstractProduct, ProductCreator>,
                            protected singleton<FactoryWithAutoId<AbstractProduct, IdentifierType, Storage, ProductCreator, FactoryErrorPolicy> >
{
public:
    typedef AbstractProduct type_abstract_product;
    typedef IdentifierType type_identifier;
    typedef ProductCreator type_product_creator;
    typedef FactoryErrorPolicy<IdentifierType, AbstractProduct> error_policy;
    typedef Storage<IdentifierType, AbstractProduct, ProductCreator> storage_policy;
    friend class singleton<FactoryWithAutoId>;

    static AbstractProduct* create(typename const_parameter_trait<IdentifierType>::type id)
    {
        FactoryWithAutoId& inst = FactoryWithAutoId::instance();
        std::size_t pos = storage_policy::pos2id(id);
        if(pos >= inst.m_containr.size()) return error_policy::onUnknownType(id);
        return inst.m_containr[pos]();
    }

    static IdentifierType registerProduct(ProductCreator creator)
    {
        FactoryWithAutoId& inst = FactoryWithAutoId::instance();
        std::size_t pos = inst.m_containr.size();
        assert((pos < trait_max_value<AbstractProduct, IdentifierType>::value()));
        inst.m_containr.push_back(creator);
        IdentifierType res = storage_policy::pos2id(pos);
        return res;
    }

private:
    FactoryWithAutoId() = default;
};

END_NAMESPACE_UTILS

#endif // FACTORYWITHAUTOID_HPP
