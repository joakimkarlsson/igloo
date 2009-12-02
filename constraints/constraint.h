#ifndef _CONSTRAINT_H
#define	_CONSTRAINT_H

template <typename T>
class IConstraint
{
public:
  virtual bool Assert(T actual, string& errorText) = 0;
};

#endif	/* _CONSTRAINT_H */

