#pragma once

#include "../core/type.hpp"
#include "tree_node.hpp"

namespace base
{
    /// @brief 节点树
    class NodeTree : public PrintableObject, public std::enable_shared_from_this<NodeTree>
    {
    public:
        /// @brief 节点树状态
        enum class Status : Int32
        {
            /// @brief 尚未初始化
            Uninitialized,
            /// @brief 正在初始化
            Initializing,
            /// @brief 已就绪
            Ready,
        };

        /// @brief 创建一个节点树
        /// @return 节点树引用
        static NodeTreeRef create();

        /// @brief 将Status枚举转换为字符串
        /// @param status Status枚举值
        /// @return 转换后的字符串
        static std::string status_str(Status status);

    private:
        /// @brief 根节点
        TreeNodeRef m_root;
        /// @brief 当前状态
        Status m_status = Status::Uninitialized;

    protected:
        NodeTree() = default;

    public:
        ~NodeTree() override = default;

    protected:
        /// @brief 当节点树初始化时
        virtual void _on_initialize() {}

        /// @brief 当节点树就绪时
        virtual void _on_ready() {}

        /// @brief 当节点树结束时
        virtual void _on_finalize() {}

    public:
        const TreeNodeRef &get_root() const { return m_root; }
        Status get_status() const { return m_status; }

    protected:
        /// @brief 强行设为根节点
        /// @param root 待设置根节点
        void _set_root(const TreeNodeRef &root);

        /// @brief 强行移除根节点
        void _remove_root();

    public:
        /// @brief 转换成字符串
        /// @return 转换后的字符串
        std::string to_string() const override;

        /// @brief 请求节点树初始化
        virtual void request_initialize();

        /// @brief 请求节点树结束
        virtual void request_finalize();
    };

    /// @brief 序列化节点树
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const NodeTree &node);

    /// @brief 序列化节点树
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const NodeTreeRef &node);

    /// @brief 序列化节点树
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const NodeTreeWeakRef &node);

} // namespace base
