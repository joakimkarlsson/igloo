/* 
 * File:   greaterthanconstraint.h
 * Author: joakim
 *
 * Created on December 18, 2009, 7:17 PM
 */

#ifndef _GREATERTHANCONSTRAINT_H
#define	_GREATERTHANCONSTRAINT_H

namespace igloo {

    template <typename T>
    class GreaterThanConstraint : public Constraint<T> {
    public:

        GreaterThanConstraint(T expected) : _expected(expected) {
        }

        bool Evaluate(T actual) {
            return actual > _expected;
        }

        std::string ExpectationText() {
            std::ostringstream str;
            str << "greater than " << _expected;
            return str.str();
        }

    private:
        T _expected;
    };

}
#endif	/* _GREATERTHANCONSTRAINT_H */

