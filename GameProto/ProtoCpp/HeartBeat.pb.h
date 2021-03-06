// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: HeartBeat.proto

#ifndef PROTOBUF_INCLUDED_HeartBeat_2eproto
#define PROTOBUF_INCLUDED_HeartBeat_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_HeartBeat_2eproto 

namespace protobuf_HeartBeat_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_HeartBeat_2eproto
namespace protobufMsg {
class HeartBeat;
class HeartBeatDefaultTypeInternal;
extern HeartBeatDefaultTypeInternal _HeartBeat_default_instance_;
}  // namespace protobufMsg
namespace google {
namespace protobuf {
template<> ::protobufMsg::HeartBeat* Arena::CreateMaybeMessage<::protobufMsg::HeartBeat>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace protobufMsg {

// ===================================================================

class HeartBeat : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:protobufMsg.HeartBeat) */ {
 public:
  HeartBeat();
  virtual ~HeartBeat();

  HeartBeat(const HeartBeat& from);

  inline HeartBeat& operator=(const HeartBeat& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  HeartBeat(HeartBeat&& from) noexcept
    : HeartBeat() {
    *this = ::std::move(from);
  }

  inline HeartBeat& operator=(HeartBeat&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const HeartBeat& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const HeartBeat* internal_default_instance() {
    return reinterpret_cast<const HeartBeat*>(
               &_HeartBeat_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(HeartBeat* other);
  friend void swap(HeartBeat& a, HeartBeat& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline HeartBeat* New() const final {
    return CreateMaybeMessage<HeartBeat>(NULL);
  }

  HeartBeat* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<HeartBeat>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const HeartBeat& from);
  void MergeFrom(const HeartBeat& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HeartBeat* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 actionId = 1;
  void clear_actionid();
  static const int kActionIdFieldNumber = 1;
  ::google::protobuf::int32 actionid() const;
  void set_actionid(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:protobufMsg.HeartBeat)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 actionid_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_HeartBeat_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// HeartBeat

// int32 actionId = 1;
inline void HeartBeat::clear_actionid() {
  actionid_ = 0;
}
inline ::google::protobuf::int32 HeartBeat::actionid() const {
  // @@protoc_insertion_point(field_get:protobufMsg.HeartBeat.actionId)
  return actionid_;
}
inline void HeartBeat::set_actionid(::google::protobuf::int32 value) {
  
  actionid_ = value;
  // @@protoc_insertion_point(field_set:protobufMsg.HeartBeat.actionId)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobufMsg

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_HeartBeat_2eproto
