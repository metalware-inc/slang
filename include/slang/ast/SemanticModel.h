//------------------------------------------------------------------------------
//! @file SemanticModel.h
//! @brief Query semantic information for a syntax tree
//
// SPDX-FileCopyrightText: Michael Popoloski
// SPDX-License-Identifier: MIT
//------------------------------------------------------------------------------
#pragma once

#include "slang/ast/symbols/BlockSymbols.h"
#include "slang/ast/symbols/CompilationUnitSymbols.h"
#include "slang/ast/symbols/InstanceSymbols.h"
#include "slang/ast/symbols/SubroutineSymbols.h"
#include "slang/ast/types/AllTypes.h"
#include "slang/util/Hash.h"

namespace slang {

struct CompilationUnitSyntax;

class SemanticModel {
public:
    explicit SemanticModel(Compilation& compilation);

    void withContext(const SyntaxNode& node, const Symbol& symbol);

    const Symbol* getDeclaredSymbol(const SyntaxNode& syntax);

    const CompilationUnitSymbol* getDeclaredSymbol(const CompilationUnitSyntax& syntax);
    const InstanceSymbol* getDeclaredSymbol(const HierarchyInstantiationSyntax& syntax);
    const StatementBlockSymbol* getDeclaredSymbol(const BlockStatementSyntax& syntax);
    const ProceduralBlockSymbol* getDeclaredSymbol(const ProceduralBlockSyntax& syntax);
    const GenerateBlockSymbol* getDeclaredSymbol(const IfGenerateSyntax& syntax);
    const GenerateBlockArraySymbol* getDeclaredSymbol(const LoopGenerateSyntax& syntax);
    const SubroutineSymbol* getDeclaredSymbol(const FunctionDeclarationSyntax& syntax);
    const EnumType* getDeclaredSymbol(const EnumTypeSyntax& syntax);
    const TypeAliasType* getDeclaredSymbol(const TypedefDeclarationSyntax& syntax);

private:
    Compilation& compilation;

    flat_hash_map<const SyntaxNode*, const Symbol*> symbolCache;
};

} // namespace slang