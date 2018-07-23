#pragma once

#define FORWARD_DECL_CLASS(x) \
class x;\
using x##ShaPtr = std::shared_ptr<x>;\
using x##UnqPtr = std::unique_ptr<x>;\
using x##WeakPtr = std::weak_ptr<x>;

#define FORWARD_DECL_NAMESPACE_CLASS(n,x) \
namespace n\
{\
class x;\
using x##ShaPtr = std::shared_ptr<x>;\
using x##UnqPtr = std::unique_ptr<x>;\
using x##WeakPtr = std::weak_ptr<x>;\
}

FORWARD_DECL_CLASS(Actor)
FORWARD_DECL_NAMESPACE_CLASS(Behavior, Composite)
FORWARD_DECL_NAMESPACE_CLASS(Behavior, GroupComposite)
FORWARD_DECL_NAMESPACE_CLASS(Behavior, Action)
FORWARD_DECL_NAMESPACE_CLASS(Behavior, Probability)
