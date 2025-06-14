#pragma once

#include <string>
#include "polymorphic_object.hpp"

namespace base
{
    /// @brief 带名字的对象
    class NamedObject : public PolymorphicObject
    {
    private:
        /// @brief 对象名
        std::string m_name;

    public:
        NamedObject(const std::string &name = {}) : m_name(name) {}
        ~NamedObject() override = default;

    protected:
        /// @brief 当对象名更改时
        /// @param old_name 旧名字
        /// @param new_name 新名字
        virtual void _on_name_changed(const std::string &old_name, const std::string &new_name) {}

    protected:
        /// @brief 直接设置对象名
        /// @param name 对象名
        void _set_name(const std::string &name) { m_name = name; }

    public:
        const std::string &get_name() const { return m_name; }

        virtual void set_name(const std::string &new_name)
        {
            if (m_name == new_name)
                return;

            std::string old_name = m_name;
            m_name = new_name;
            _on_name_changed(old_name, new_name);
        }
    };

} // namespace base
