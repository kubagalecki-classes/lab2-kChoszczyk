#pragma once

#include "Resource.hpp"

class ResourceManager
{
public:
    ResourceManager()
    {
        res = new Resource;
    }
    ResourceManager(const ResourceManager& resMan)
    {
        res        = new Resource;
        *this->res = *resMan.res;
    }
    ResourceManager(ResourceManager&&) {res        = new Resource;
        *this->res = *resMan.res;
        delete resMan.res; }
    ResourceManager& operator=(const ResourceManager&)
    {
        return *this;
    }
    ResourceManager& operator=(ResourceManager&&)
    {
        return *this;
        delete resMan.res;
    }
    ~ResourceManager()
    {
        delete res;
    }

    Resource* res;

    double get()
    {
        return res->get();
    }
};
