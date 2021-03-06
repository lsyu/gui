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

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "basic2dentity.h"
#include "rectangletext.h"
#include "rectangledecoration.h"

#include "core/ogl/vertexbufferobject.h"
#include "core/ogl/vertexarrayobject.h"

namespace bhm {

class CShader;
class CTexture;

/**
 * @brief Прямоугольник.
 *
 * Данная сущность генерирует и выводит на экран прямоугольник с заданными параметрами.
 */
class CRectangle : public CBasic2dEntity
{
public:
    CRectangle();
    explicit CRectangle(const std::string &m_id);
    virtual ~CRectangle();

    // AbstractEntity interface
public:
    virtual void paint() const override;
    virtual void configure() override;
    // CBasic2dEntity interface
public:
    virtual float getXMin() const override;
    virtual float getXMax() const override;
    virtual float getYMin() const override;
    virtual float getYMax() const override;
    virtual void onClicked(const CEventMouseClick &event) override;

public:
    void setColor(const glm::vec3 &color);
    glm::vec3 getColor() const;
    /**
     * @brief Установить координату X левого нижнего угла прямоугольника.
     * @note Плоскость монитора ограничивается интервалом [-1, 1].
     */
    void setX(float x);
    /**
     * @brief Установить координату Y левого нижнего угла прямоугольника.
     * @note Плоскость монитора ограничивается интервалом [-1, 1].
     */
    void setY(float y);
    /**
     * @brief Установить длину.
     * @note Плоскость монитора ограничивается интервалом [-1, 1].
     * @note Длина  - неотрицательное значение!
     */
    void setWidth(float width);
    float getWidth() const;
    /**
     * @brief Установить высоту.
     * @note Плоскость монитора ограничивается интервалом [-1, 1].
     * @note Высота - неотрицательное значение!
     */
    void setHeight(float height);
    float getHeight() const;
    /**
     * @brief Установить границу
     */
    void setRadius(const CBorderRadius &radius);
    CBorderRadius getRadius() const;
    /**
     * @brief Установить границу
     */
    void setBorder(const CBorder &border);
    CBorder getBorder() const;
    /**
     * @brief Получение текстуры при помощи менеджера текстур.
     * @param name имя файла текстуры без расширения .dds
     */
    void setTexture(const std::string &name);
    std::string getTexture() const;
    /**
     * @brief Получение градиента.
     * @param gradient градиент.
     */
    void setGradient(const CGradient &gradient);
    CGradient getGradient() const;
    /**
     * @brief Получение прозрачности.
     *
     * @note 0 - полностью прозрачный, 1 - полностью непрозрачный.
     */
    void setAlpha(float alpha);
    float getAlpha() const;
    /**
     * @brief Получение текста для данного прямоугольника
     * @param text текст
     */
    void setText(const CRectangleText &text);
    CRectangleText getText() const;

protected:
    /**
     * @brief Содержит ли фигура точку point
     */
    bool contains(const glm::vec2 &point) const;

    float m_aspect;         /**< Соотношение сторон окна. */
    float m_alpha;          /**< Прозрачность. */
    glm::vec4 m_size;       /**< Рамеры: (x, y, width, height) */
    CBorder m_border;       /**< Грань прямоугольника. */
    CBorderRadius m_radius; /**< Радиус сторон прямоугольника. */
    CTexture *m_texture;     /**< Текстура. */
    CRectangleText m_text;  /**< Текст. */
}; //class Rectangle

} // namespace behemoth

#endif // RECTANGLE_H
