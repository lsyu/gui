/*
 * Labs4Physics - visualisation of physics process
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

#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "lua/lua.h"

namespace core {

class CBasic2dEntity;

/**
 * @brief Менеджер работы с Lua.
 *
 * Архитектура - singleton. @n
 * Позволяет декларативно описывать данные, используя язык Lua. @n
 *
 * На данный момент есть возможность загрузки элементов графического пользовательского интерфейса,
 * а также загрузка путей ресурсов. @n
 * Элементы GUI:
 * - glm::vec2 - 2хмерный вектор
 * - glm::vec3 - 3хмерный вектор
 * - ui:rectangle - прямоугольник
 * - ui:border - грани прямоугольника
 * - ui:radius - радиус скруглений углов прямоугольника
 * - ui:text - текст для вывода
 *
 * @todo Пример описания интерфейса
 *
 */
class CGUIManager
{
public:
    /**
     * @brief Получить экземпляр менеджера работы с Lua.
     */
    static CGUIManager *getInstance();

    /**
     * @brief Прочитать файл описания интерфейса с именем @a fileName.
     *
     * После парсинга скрипта луа наши декларативно описанные элементы
     * сохраняются в вектор, получить доступ к которым можно, воспользовавшись
     * методами @sa getObject, getObjects
     * @return true если скрипт выполнен, false в противном случае.
     */
    bool readGui(const std::string &fileName);

    CBasic2dEntity *getObject(const std::string &id);
    CBasic2dEntity *getObject(int num);
    CBasic2dEntity *getRootObject();
    const std::vector<std::shared_ptr<CBasic2dEntity> > &getObjects() const;

    /**
     * @brief Выполнить onClick из скрипта Lua.
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    bool onClick(CBasic2dEntity *entity);
    /**
     * @brief Выполнить onPressed из скрипта Lua.
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    bool onPressed(CBasic2dEntity *entity);
    /**
     * @brief Выполнить onReleased из скрипта Lua.
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    bool onReleased(CBasic2dEntity *entity);

protected:
    /**
     * @brief добавить готовый объект в контейнер на вывод.
     */
    template<class T>
    void addObject(CBasic2dEntity *entity);
    /**
     * @brief Инициализация и регистрирование всех доп. возможностей.
     */
    void init();
    /**
     * @brief Закрытие.
     */
    void close();
    /**
     * @brief Регистрация таблицы ui
     */
    void registerUI();
    /**
     * @brief Регистрация glm::vec2
     */
    void registerVec2();
    /**
     * @brief Регистрация glm::vec3
     */
    void registerVec3();
    /**
     * @brief регистрация core::CBorder
     */
    void registerBorder();
    /**
     * @brief регистрация core::CGradient
     */
    void registerGradient();
    /**
     * @brief Регистрация core::RectangleText.
     */
    void registerText();
    /**
     * @brief Регистрация core::Rectangle.
     */
    void registerRectangle();

    /**
     * @brief Выполнить действие из скрипта в lua
     * @return true, если все хорошо. В случае, если не удастся выполнить действие, вернется false.
     */
    bool executeAction(CBasic2dEntity *entity, const std::string &action);

private:
    CGUIManager();
    ~CGUIManager();
    CGUIManager(const CGUIManager &);
    CGUIManager &operator=(const CGUIManager&);

    static CGUIManager *instance;
    lua_State *lua;
    std::vector< std::shared_ptr<core::CBasic2dEntity> > objects; /**< Элементы GUI */

    friend class __CGUIManagerImplDel;
}; // class CGUIManager

} // namespace Core

#endif // GUIMANAGER_H
