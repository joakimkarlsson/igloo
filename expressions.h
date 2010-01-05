#ifndef _EXPRESSIONS_H_
#define _EXPRESSIONS_H_

#include <string>
#include <stack>
#include <memory>
#include <list>
#include <sstream>

#include "expressions/constraints/constraint.h"

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

#include "expressions/expressionitem.h"

#endif
