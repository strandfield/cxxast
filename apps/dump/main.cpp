// Copyright (C) 2020 Vincent Chambrin
// This file is part of the 'cxxast' project
// For conditions of distribution and use, see copyright notice in LICENSE

#include "cxx/libclang.h"

#include "cxx/clang/clang-cursor.h"
#include "cxx/clang/clang-index.h"
#include "cxx/clang/clang-translation-unit.h"

#include <iostream>

using namespace cxx;

int depth = 0;

void visit(ClangCursor c)
{
  std::cout << std::string(static_cast<size_t>(depth), ' ');

  std::cout << c.getCursorKingSpelling() << ": " << c.getSpelling() << std::endl;

  {
    ++depth;

    c.visitChildren([](ClangCursor child) {
      visit(child);
      });

    --depth;
  }
}

void work(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "argc must be >= 2" << std::endl;
    return;
  }

  LibClang libclang;

  ClangIndex index = libclang.createIndex();

  std::string file{ argv[1] };
  ClangTranslationUnit tu = index.parseTranslationUnit(file, {}, CXTranslationUnit_SkipFunctionBodies);

  ClangCursor cursor = tu.getCursor();

  cursor.visitChildren([](ClangCursor c) {
    visit(c);
    });
}

int main(int argc, char *argv[])
{
  try
  {
    work(argc, argv);
  }
  catch (cxx::LibClangError & err)
  {
    std::cerr << "could not find libclang" << std::endl;
    return 1;
  }
  catch (std::runtime_error & err)
  {
    std::cerr << err.what() << std::endl;
    return 2;
  }

  return 0;
}