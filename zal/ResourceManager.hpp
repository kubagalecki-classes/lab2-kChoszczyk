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
    ResourceManager(ResourceManager&&) {
      //res        = new Resource;
        //*this->res = resMan.res;
        //delete resMan.res; 
        }
    ResourceManager& operator=(const ResourceManager&)
    {
      res = new Resource;
        return *this;
    }
    ResourceManager& operator=(ResourceManager&& resMan)
    {
        return *this;
        //delete resMan;
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
