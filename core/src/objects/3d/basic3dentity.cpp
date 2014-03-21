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

#include "basic3dentity.h"

#include <algorithm>

#include "core/objects/3d/camerafactory.h"

#include "core/ogl/ogl.h"
#include "core/ogl/shaderfactory.h"

namespace core {

CBasic3dEntity::CBasic3dEntity(const std::string &id) : AbstractEntity(), mId(id), mChilds(), mParent(nullptr),
    mVertixes(), mUVs(), mIndexes(), mNormals(), mVAO(), mVertexVBO(), mIndexVBO(EArrayType::Index)
{
}

CBasic3dEntity::~CBasic3dEntity()
{
    for(CBasic3dEntity *item: mChilds)
        delete item;
}

void CBasic3dEntity::configure()
{
    mVAO.genBuffer();
    mVAO.bind();

    mVertexVBO.genBuffer();
    mVertexVBO.setData(&mVertixes);

    mIndexVBO.genBuffer();
    mIndexVBO.setData(&mIndexes);

    mVAO.disable();

    for (CBasic3dEntity *obj: mChilds)
        obj->configure();
}

void CBasic3dEntity::paint() const
{
    static AbstractCamera *cam = CCameraFactory::getInstance()->getActiveCamera();
    if (cam) {
        CShader *shader = CShaderFactory::getInstance()->getShader("test"); //! TODO: Вынести в CMaterial
        static glm::mat4 model; //! TODO: Вынести в CSceneNode

        if (shader) {
            shader->setUniform("modelview_matrix", model * cam->getViewMatrix());
            shader->setUniform("projection_matrix", cam->getProjectionMatrix());

            // Индексы - unsigned short int по 3 на полигон
            mVAO.bind();
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, (void*)0);
            glDrawElements(GL_TRIANGLES, mIndexes.size() * 3, GL_UNSIGNED_SHORT, static_cast<void*>(0));
            glDisableVertexAttribArray(0);
            mVAO.disable();
        }

        for (CBasic3dEntity *obj: mChilds)
            obj->paint();
    }
}

std::string CBasic3dEntity::getId() const
{
    return mId;
}

void CBasic3dEntity::setParent(CBasic3dEntity *parent)
{
    mParent = parent;
}

CBasic3dEntity *CBasic3dEntity::getParent() const
{
    return mParent;
}

bool CBasic3dEntity::isRoot() const
{
    return mParent == nullptr;
}

void CBasic3dEntity::addChild(CBasic3dEntity *child)
{
    mChilds.push_back(child);
}

CBasic3dEntity *CBasic3dEntity::getChild(const std::string &id)
{
    CChilds3D::const_iterator it = std::find_if(mChilds.begin(), mChilds.end(),
    [&id](CBasic3dEntity *child) -> bool
    {
        return child->getId() == id;
    });
    if (it != mChilds.end())
        return (CBasic3dEntity *)(&(*it));
    return nullptr;
}

std::vector<CBasic3dEntity *> &CBasic3dEntity::getChilds()
{
    return mChilds;
}

} // namespace core