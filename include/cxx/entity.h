// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'cxxast' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef CXXAST_ENTITY_H
#define CXXAST_ENTITY_H

#include "cxx/node.h"

#include "cxx/access-specifier.h"

namespace cxx
{

class Documentation;

class CXXAST_API IEntity : public INode
{
public:
  std::string name;
  std::weak_ptr<IEntity> weak_parent;
  std::shared_ptr<Documentation> documentation;

public:
  explicit IEntity(std::string name, std::shared_ptr<IEntity> parent = nullptr);

  std::shared_ptr<IEntity> shared_from_this();
  std::shared_ptr<const IEntity> shared_from_this() const;

  bool isEntity() const override;

  std::shared_ptr<IEntity> parent() const;

  virtual AccessSpecifier getAccessSpecifier() const;
  virtual void setAccessSpecifier(AccessSpecifier aspec);

  struct Name : public priv::Field<IEntity, std::string>
  {
    static std::string& get(INode& n)
    {
      return down_cast(n).name;
    }

    static void set(INode& n, std::string name)
    {
      down_cast(n).name = std::move(name);
    }
  };
};

class CXXAST_API Entity
{
protected:
  std::shared_ptr<IEntity> d;

public:
  Entity() = default;
  Entity(const Entity&) = default;
  ~Entity() = default;

  Entity(std::shared_ptr<IEntity> impl)
    : d(std::move(impl))
  {

  }

  bool isNull() const { return d == nullptr; }

  NodeKind kind() const { return d->node_kind(); }

  Entity parent() const { return d->parent(); }

  AccessSpecifier accessSpecifier() const { return d->getAccessSpecifier(); }

  template<typename T>
  bool is() const { return d->is<T>(); }

  template<typename F>
  typename F::field_type& get() const { return d->get<F>(); }

  template<typename F, typename Arg>
  void set(Arg&& value) { return d->set<F>(std::forward<Arg>(value)); }

  const std::shared_ptr<IEntity>& impl() const { return d; }

  Entity& operator=(const Entity&) = default;
};

inline bool operator==(const Entity& lhs, const Entity& rhs)
{
  return lhs.impl() == rhs.impl();
}

inline bool operator!=(const Entity& lhs, const Entity& rhs)
{
  return lhs.impl() != rhs.impl();
}

} // namespace cxx

namespace cxx
{

inline IEntity::IEntity(std::string n, std::shared_ptr<IEntity> parent)
  : name(std::move(n)),
    weak_parent(parent)
{

}

inline std::shared_ptr<IEntity> IEntity::parent() const
{
  return weak_parent.lock();
}

} // namespace cxx

#endif // CXXAST_ENTITY_H
