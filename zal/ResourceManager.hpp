#pragma once

#include "Resource.hpp"

class ResourceManager
{
public:
    ResourceManager() : res(*new Resource) {}

    ResourceManager(const ResourceManager& arg) : res(*new Resource = arg.res) {}

    ResourceManager(ResourceManager&& arg) : res(arg.res) {}

    ResourceManager& operator=(const ResourceManager& arg)
    {
        res = arg.res;
        return *this;
    }

    ResourceManager& operator=(ResourceManager&&) { return *this; }

    ~ResourceManager() { delete &res; }

    Resource& res;

    double get() { return (res.get()); }
};
