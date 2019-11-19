#define DECLARE_HAS_MEMBER(NAME) \
template<class T, typename... Args> \
struct has_member_##NAME \
{                           \
  template<class U> \
  constexpr static auto check(void*)->decltype(std::decval<T>().NAME(std::decval<Args>()...), std::true_type()); \
  
  template<class U> \
  constexpr static std::false_type() check(...); \
  constexpr static bool value = decltype(check<T>(nullptr))::value; \
};

#define HAS_CLASS_MEMBER(CLASS, MEMBER, ...) \
has_member_##MEMBER(CLASS, __VA_ARGS__)::value;
