#ifndef STATEFACTORY_HPP
#define STATEFACTORY_HPP

#include "state.hpp"

#include <utils/factorywithautoid.hpp>

#include <ui/tooltipsingleton.hpp>

struct StateFactory
{
    typedef utils::FactoryWithAutoId<State> type_factory;
    typedef type_factory::type_identifier type_identifier;

    static type_factory::type_identifier registerProduct(type_factory::type_product_creator creator, std::string&& tooltip, std::string&& icone) {
        type_factory::type_identifier id = type_factory::registerProduct(creator);
        ToolTipSingleton::addToolButton(id, std::move(tooltip), std::move(icone));
        return id;
    }

    static type_factory::type_abstract_product* create(typename utils::const_parameter_trait<type_identifier>::type id)
    {
        return type_factory::create(id);
    }
};

#endif // STATEFACTORY_HPP
