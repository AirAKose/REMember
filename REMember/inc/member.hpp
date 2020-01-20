#pragma once

#include "type_traits.hpp"


template<auto Member, auto ... MemPtrList>
constexpr inline auto& member_resolve_all(get_member_owner_t<decltype(Member)>* elem)
{
    constexpr std::size_t remaining = get_count<MemPtrList...>::value;
    if constexpr (remaining == 0)
    {
        return elem->*Member;
    }
    else
    {
        if constexpr (std::is_pointer_v<decltype(elem->*Member)>)
        {
            return member_resolve_all<MemPtrList...>(elem->*Member);
        }
        else
        {
            return member_resolve_all<MemPtrList...>(&(elem->*Member));
        }
    }
};

template<auto ... MemberPtrs>
class member
{
    static_assert(get_count_v<MemberPtrs...> > 0, "member class requires at least one valid member pointer");


private:
    using first_type = get_first_type_t<decltype(MemberPtrs)...>;
    using last_type = get_last_type_t<decltype(MemberPtrs)...>;
    using root_type = get_member_owner_t<first_type>;

public:
    using type = get_member_type_t<last_type>;
    using pointer = std::add_pointer_t<type>;
    using const_pointer = std::add_pointer_t<std::add_const_t<type>>;
    using reference = std::add_lvalue_reference_t<type>;
    using const_reference = std::add_const_t<reference>;

    static constexpr pointer get_ptr(root_type& source) noexcept
    {
        return &member_resolve_all<MemberPtrs...>(&source);
    }

    static constexpr const_pointer get_ptr(const root_type& source) noexcept
    {
        return &member_resolve_all<MemberPtrs...>(&source);
    }

    static constexpr reference get_ref(root_type& source) noexcept
    {
        return member_resolve_all<MemberPtrs...>(&source);
    }

    static constexpr const_reference get_ref(const root_type& source) noexcept
    {
        return member_resolve_all<MemberPtrs...>(&source);
    }

    constexpr inline reference operator()(root_type& source) noexcept { return get_ref(source); }
};