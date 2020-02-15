// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'cxxast' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "cxx/entity.h"

namespace cxx
{

std::shared_ptr<Entity> Entity::shared_from_this()
{
  return std::static_pointer_cast<Entity>(Node::shared_from_this());
}

bool Entity::isEntity() const
{
  return true;
}

} // namespace cxx
