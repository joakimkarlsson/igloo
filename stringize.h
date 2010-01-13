#ifndef IGLOO_STRINGIZE_H
#define IGLOO_STRINGIZE_H

namespace igloo {
   namespace detail {

      // A tag type returned by operator == for the any struct in this namespace
      // when T does not support ==.
      struct tag {};

      // This type soaks up any implicit conversions and makes the following operator<<
      // less preferred than any other such operator found via ADL.
      struct any
      {
         // Conversion constructor for any type.
         template <class T>
         any(T const&);
      };

      // Fallback operator<< for types T that don't support <<.
      tag operator<<(std::ostream&, any const&);

      // Two overloads to distinguish whether T supports a certain operator expression.
      // The first overload returns a reference to a two-element character array and is chosen if
      // T does not support the expression, such as <<, whereas the second overload returns a char 
      // directly and is chosen if T supports the expression. So using sizeof(check(<expression>))
      // returns 2 for the first overload and 1 for the second overload.
      typedef char yes;
      typedef char (&no)[2];

      no check(tag);

      template <class T>
      yes check(T const&);

      template <class T>
      struct is_output_streamable_impl
      {
         // Should use boost.typetraits to peel off cv-qualifiers, pointer and/or reference decoration from T
         static const T& x;

         static const bool value = sizeof(check(std::cout << x)) == sizeof(yes);
      };
   }

   template <class T>
   struct is_output_streamable : detail::is_output_streamable_impl<T> {};

   template<typename T, bool type_is_streamable>
   struct Stringizer
   {
      static std::string Convert(const T& value)
      {
         std::ostringstream buf;
         buf << value;
         return buf.str();
      }
   };

   template<typename T>
   struct Stringizer<T, false>
   {
      static std::string Convert(const T& value)
      {
         return "unsupported type";
      }
   };

   template<typename T>
   std::string Stringize(const T& t)
   {
      return Stringizer< T, is_output_streamable<T>::value >::Convert(t);
   }
}

#endif