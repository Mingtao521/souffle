/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2020, The Souffle Developers. All rights reserved.
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file PolymorphicObjects.cpp
 *
 ***********************************************************************/

#include "ast/analysis/PolymorphicObjects.h"
#include "ast/Aggregator.h"
#include "ast/BinaryConstraint.h"
#include "ast/IntrinsicFunctor.h"
#include "ast/NumericConstant.h"
#include "ast/TranslationUnit.h"
#include "ast/utility/Visitor.h"
#include "souffle/utility/ContainerUtil.h"

namespace souffle::ast::analysis {

void PolymorphicObjectsAnalysis::run(const TranslationUnit& translationUnit) {
    typeAnalysis = translationUnit.getAnalysis<analysis::TypeAnalysis>();
}

void PolymorphicObjectsAnalysis::print(std::ostream& /* os */) const {}

FunctorOp PolymorphicObjectsAnalysis::getOverloadedFunctionOp(const IntrinsicFunctor* inf) const {
    const auto& op = inf->getFunctionOp();
    if (op) return op.value();
    return FunctorOp::ORD;
}

NumericConstant::Type PolymorphicObjectsAnalysis::getInferredType(const NumericConstant* nc) const {
    return typeAnalysis->getPolymorphicNumericConstantType(nc);
}

bool PolymorphicObjectsAnalysis::hasInvalidType(const NumericConstant* nc) const {
    return typeAnalysis->hasInvalidPolymorphicNumericConstantType(nc);
}

BinaryConstraintOp PolymorphicObjectsAnalysis::getOverloadedOperator(const BinaryConstraint* bc) const {
    return bc->getOperator();
}

AggregateOp PolymorphicObjectsAnalysis::getOverloadedOperator(const Aggregator* aggr) const {
    return typeAnalysis->getPolymorphicOperator(aggr);
}

}  // namespace souffle::ast::analysis
