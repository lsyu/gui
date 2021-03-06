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

#ifndef LIGHTFACTORY_H
#define LIGHTFACTORY_H

#include "pointlight.h"
#include "directionlight.h"

#include <string>
#include <map>

namespace bhm {

/**
 * @brief Тип источника освещения
 */
enum class ELightType: unsigned char {
    point,      /**< Точечный.  */
    direction,  /**< Направленный. */
    all         /**< Любой. */
}; // enum EMouseButton

/**
 * @brief Фабрика загрузки источников освещения.
 */
class CLightFactory
{
public:
    /**
     * @brief Получить экземпляр фабрики источников освещения.
     * @return экземпляр фабрики источников освещения.
     */
    static CLightFactory* getInstance();

    /**
     * @brief Получить источник освещения по имени.
     * @param name имя источника освещения.
     * @param тип источника освещения.
     * @return источник освещения с заданным именем.
     * @note Перед получением источник освещения его нужно создать при помощи @a makeLight.
     * @note в случае невозможности получить источник освещения с заданными параметрами возвращает nullptr.
     */
    CPointLight *getLight(const std::string &name, ELightType type = ELightType::all) const;

    /**
     * @brief Получить ближайший к заданной точке источник освещения.
     * @param точка, по отношению к которой ищется источник освещения.
     * @note в случае невозможности получить источник освещения с заданными параметрами возвращает nullptr.
     */
    CPointLight *getNearestLight(const glm::vec3 &point) const;

    /**
     * @brief Создать источник освещения.
     * @param name имя источника освещения.
     * @param type тип источника освещения.
     * @note Если источник с заданным именем и типом уже существет, источник освещения не будет создан!
     * @note Если тип источника освещения равен ELightType::all, , источник освещения не будет создан!
     */
    void makeLight(const std::string &name, ELightType type);

private:
    CLightFactory();
    ~CLightFactory();
    CLightFactory(const CLightFactory &);
    CLightFactory &operator=(const CLightFactory &);

    static CLightFactory *instance;
    std::map<std::pair<std::string, ELightType>, CPointLight*> m_lights;

    friend class __CLightFactoryImplDel;
}; // class CLightFactory

} // namespace behemoth

#endif // LIGHTFACTORY_H
