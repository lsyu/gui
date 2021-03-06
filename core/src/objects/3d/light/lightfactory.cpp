/*
 * behemoth is graphics engine with lua-based declarative language for designing user interface and 3d stuff.
 * Copyright (C) 2013  Leyko Sergey powt81lsyu@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "lightfactory.h"
#include <limits>

namespace bhm {

CLightFactory *CLightFactory::instance = nullptr;

class __CLightFactoryImplDel {
public:
    explicit __CLightFactoryImplDel(CLightFactory *obj) : obj(obj) {}
    ~__CLightFactoryImplDel() {delete obj;}
private:
    CLightFactory *obj;
}; // class __CLightFactoryImplDel

CLightFactory *CLightFactory::getInstance()
{
    if (!instance) {
        instance = new CLightFactory;
        static __CLightFactoryImplDel impDel(instance);
    }
    return instance;
}

CPointLight *CLightFactory::getLight(const std::string &name, ELightType type) const
{
    if (type == ELightType::all) {
        std::map<std::pair<std::string, ELightType>, CPointLight*>::const_iterator it
                = m_lights.find(std::pair<std::string, ELightType>(name, ELightType::point));
        if(it != m_lights.end())
            return static_cast<CPointLight*>(it->second);
        it = m_lights.find(std::pair<std::string, ELightType>(name, ELightType::direction));
        if(it != m_lights.end())
            return static_cast<CDirectionLight*>(it->second);
        return nullptr;
    }

    std::map<std::pair<std::string, ELightType>, CPointLight*>::const_iterator it
            = m_lights.find(std::pair<std::string, ELightType>(name, type));
    if(it != m_lights.end()) {
        if (type == ELightType::point)
            return static_cast<CPointLight*>(it->second);
        static_cast<CDirectionLight*>(it->second);
    }
    return nullptr;
}

CPointLight *CLightFactory::getNearestLight(const glm::vec3 &point) const
{
    float distance = std::numeric_limits<float>::max();
    CPointLight *ret = nullptr;
    for (auto it = m_lights.cbegin(), end = m_lights.cend(); it != end; ++it) {
        float distanceTest = glm::distance(point, it->second->getPosition());
        if (distanceTest < distance) {
            distanceTest = distance;
            ret = &(*it->second);
        }
    }
    return ret;
}

void CLightFactory::makeLight(const std::string &name, ELightType type)
{
    if (type == ELightType::all)
        return;

    CPointLight *light = nullptr;
    if (type == ELightType::direction)
        light = new CDirectionLight;
    else if (type == ELightType::point)
        light = new CPointLight;
    if (light)
        m_lights[std::pair<std::string, ELightType>(name, type)] = light;
}

CLightFactory::CLightFactory() : m_lights()
{
}

CLightFactory::~CLightFactory()
{
    for (auto item : m_lights)
        delete item.second;
}

} // namespace behemoth
