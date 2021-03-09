// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'cxxast' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "cxx/statement.h"

#include "cxx/astnodelist_p.h"

namespace cxx
{

std::shared_ptr<IStatement> IStatement::shared_from_this()
{
  return std::static_pointer_cast<IStatement>(INode::shared_from_this());
}

bool IStatement::isStatement() const
{
  return true;
}

void IStatement::append(std::shared_ptr<AstNode> n)
{
  childvec.push_back(n);
  n->weak_parent = std::static_pointer_cast<AstNode>(shared_from_this());
}

AstNodeList IStatement::children() const
{
  return AstNodeList(std::make_shared<AstVectorRefNodeList>(childvec));
}

UnexposedStatement::UnexposedStatement()
{

}

NodeKind UnexposedStatement::node_kind() const
{
  return UnexposedStatement::ClassNodeKind;
}

} // namespace cxx
