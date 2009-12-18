/* 
 * File:   lessthanconstraint.h
 * Author: joakim
 *
 * Created on December 18, 2009, 11:24 PM
 */

#ifndef _LESSTHANCONSTRAINT_H
#define	_LESSTHANCONSTRAINT_H

namespace igloo {

    template <typename T>
    class LessThanConstraint : public Constraint<T> {
    public:

        LessThanConstraint(T expected) : _expected(expected) {
        }

        bool Evaluate(T actual) {
            return actual < _expected;
        }

        std::string ExpectationText() {
            std::ostringstream str;
            str << "less than " << _expected;
            return str.str();
        }

    private:
        T _expected;
    };

}

#endif	/* _LESSTHANCONSTRAINT_H */

