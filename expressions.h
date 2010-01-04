#ifndef IGLOO_EXPRESSIONS_H
#define IGLOO_EXPRESSIONS_H

#include <string>
#include <stack>
#include <memory>
#include <list>
#include <sstream>

#include "expressions/itoken.h"
#include "expressions/constraints/constraint.h"
#include "expressions/expression.h"

#include "expressions/operators/operator.h"
#include "expressions/operators/andoperator.h"
#include "expressions/operators/notoperator.h"

#include "expressions/constraints/equaltoconstraint.h"
#include "expressions/constraints/greaterthanconstraint.h"
#include "expressions/constraints/lessthanconstraint.h"

#include "expressions/constraints/strings/stringcontainingconstraint.h"
#include "expressions/constraints/strings/stringendingwithconstraint.h"
#include "expressions/constraints/strings/stringoflengthconstraint.h"
#include "expressions/constraints/strings/stringstartingwithconstraint.h"

#endif
