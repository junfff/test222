// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: register.proto

#include "register.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace protobufMsg {
class Register_CSDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Register_CS>
      _instance;
} _Register_CS_default_instance_;
class Register_SCDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Register_SC>
      _instance;
} _Register_SC_default_instance_;
}  // namespace protobufMsg
namespace protobuf_register_2eproto {
static void InitDefaultsRegister_CS() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::protobufMsg::_Register_CS_default_instance_;
    new (ptr) ::protobufMsg::Register_CS();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::protobufMsg::Register_CS::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_Register_CS =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsRegister_CS}, {}};

static void InitDefaultsRegister_SC() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::protobufMsg::_Register_SC_default_instance_;
    new (ptr) ::protobufMsg::Register_SC();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::protobufMsg::Register_SC::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_Register_SC =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsRegister_SC}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_Register_CS.base);
  ::google::protobuf::internal::InitSCC(&scc_info_Register_SC.base);
}

::google::protobuf::Metadata file_level_metadata[2];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::protobufMsg::Register_CS, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::protobufMsg::Register_CS, accountid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::protobufMsg::Register_CS, name_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::protobufMsg::Register_CS, mobilephone_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::protobufMsg::Register_CS, email_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::protobufMsg::Register_CS, sex_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::protobufMsg::Register_CS, pwd_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::protobufMsg::Register_SC, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::protobufMsg::Register_SC, code_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::protobufMsg::Register_CS)},
  { 11, -1, sizeof(::protobufMsg::Register_SC)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::protobufMsg::_Register_CS_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::protobufMsg::_Register_SC_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "register.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\016register.proto\022\013protobufMsg\"l\n\013Registe"
      "r_CS\022\021\n\taccountId\030\001 \001(\t\022\014\n\004name\030\002 \001(\t\022\023\n"
      "\013mobilephone\030\003 \001(\t\022\r\n\005email\030\004 \001(\t\022\013\n\003sex"
      "\030\005 \001(\005\022\013\n\003pwd\030\006 \001(\t\"\033\n\013Register_SC\022\014\n\004co"
      "de\030\001 \001(\005b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 176);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "register.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_register_2eproto
namespace protobufMsg {

// ===================================================================

void Register_CS::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Register_CS::kAccountIdFieldNumber;
const int Register_CS::kNameFieldNumber;
const int Register_CS::kMobilephoneFieldNumber;
const int Register_CS::kEmailFieldNumber;
const int Register_CS::kSexFieldNumber;
const int Register_CS::kPwdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Register_CS::Register_CS()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_register_2eproto::scc_info_Register_CS.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:protobufMsg.Register_CS)
}
Register_CS::Register_CS(const Register_CS& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  accountid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.accountid().size() > 0) {
    accountid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.accountid_);
  }
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.name().size() > 0) {
    name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  mobilephone_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.mobilephone().size() > 0) {
    mobilephone_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.mobilephone_);
  }
  email_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.email().size() > 0) {
    email_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.email_);
  }
  pwd_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.pwd().size() > 0) {
    pwd_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.pwd_);
  }
  sex_ = from.sex_;
  // @@protoc_insertion_point(copy_constructor:protobufMsg.Register_CS)
}

void Register_CS::SharedCtor() {
  accountid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  mobilephone_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  email_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  pwd_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  sex_ = 0;
}

Register_CS::~Register_CS() {
  // @@protoc_insertion_point(destructor:protobufMsg.Register_CS)
  SharedDtor();
}

void Register_CS::SharedDtor() {
  accountid_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  mobilephone_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  email_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  pwd_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void Register_CS::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* Register_CS::descriptor() {
  ::protobuf_register_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_register_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Register_CS& Register_CS::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_register_2eproto::scc_info_Register_CS.base);
  return *internal_default_instance();
}


void Register_CS::Clear() {
// @@protoc_insertion_point(message_clear_start:protobufMsg.Register_CS)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  accountid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  mobilephone_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  email_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  pwd_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  sex_ = 0;
  _internal_metadata_.Clear();
}

bool Register_CS::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:protobufMsg.Register_CS)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string accountId = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_accountid()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->accountid().data(), static_cast<int>(this->accountid().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "protobufMsg.Register_CS.accountId"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string name = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->name().data(), static_cast<int>(this->name().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "protobufMsg.Register_CS.name"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string mobilephone = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_mobilephone()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->mobilephone().data(), static_cast<int>(this->mobilephone().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "protobufMsg.Register_CS.mobilephone"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string email = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u /* 34 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_email()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->email().data(), static_cast<int>(this->email().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "protobufMsg.Register_CS.email"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 sex = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(40u /* 40 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &sex_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string pwd = 6;
      case 6: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(50u /* 50 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_pwd()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->pwd().data(), static_cast<int>(this->pwd().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "protobufMsg.Register_CS.pwd"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:protobufMsg.Register_CS)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:protobufMsg.Register_CS)
  return false;
#undef DO_
}

void Register_CS::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:protobufMsg.Register_CS)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string accountId = 1;
  if (this->accountid().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->accountid().data(), static_cast<int>(this->accountid().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.accountId");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->accountid(), output);
  }

  // string name = 2;
  if (this->name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->name().data(), static_cast<int>(this->name().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->name(), output);
  }

  // string mobilephone = 3;
  if (this->mobilephone().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mobilephone().data(), static_cast<int>(this->mobilephone().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.mobilephone");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->mobilephone(), output);
  }

  // string email = 4;
  if (this->email().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->email().data(), static_cast<int>(this->email().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.email");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->email(), output);
  }

  // int32 sex = 5;
  if (this->sex() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->sex(), output);
  }

  // string pwd = 6;
  if (this->pwd().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->pwd().data(), static_cast<int>(this->pwd().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.pwd");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      6, this->pwd(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:protobufMsg.Register_CS)
}

::google::protobuf::uint8* Register_CS::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:protobufMsg.Register_CS)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string accountId = 1;
  if (this->accountid().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->accountid().data(), static_cast<int>(this->accountid().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.accountId");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->accountid(), target);
  }

  // string name = 2;
  if (this->name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->name().data(), static_cast<int>(this->name().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->name(), target);
  }

  // string mobilephone = 3;
  if (this->mobilephone().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mobilephone().data(), static_cast<int>(this->mobilephone().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.mobilephone");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->mobilephone(), target);
  }

  // string email = 4;
  if (this->email().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->email().data(), static_cast<int>(this->email().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.email");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->email(), target);
  }

  // int32 sex = 5;
  if (this->sex() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->sex(), target);
  }

  // string pwd = 6;
  if (this->pwd().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->pwd().data(), static_cast<int>(this->pwd().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "protobufMsg.Register_CS.pwd");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        6, this->pwd(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protobufMsg.Register_CS)
  return target;
}

size_t Register_CS::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobufMsg.Register_CS)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string accountId = 1;
  if (this->accountid().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->accountid());
  }

  // string name = 2;
  if (this->name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());
  }

  // string mobilephone = 3;
  if (this->mobilephone().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->mobilephone());
  }

  // string email = 4;
  if (this->email().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->email());
  }

  // string pwd = 6;
  if (this->pwd().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->pwd());
  }

  // int32 sex = 5;
  if (this->sex() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->sex());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Register_CS::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:protobufMsg.Register_CS)
  GOOGLE_DCHECK_NE(&from, this);
  const Register_CS* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Register_CS>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:protobufMsg.Register_CS)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:protobufMsg.Register_CS)
    MergeFrom(*source);
  }
}

void Register_CS::MergeFrom(const Register_CS& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protobufMsg.Register_CS)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.accountid().size() > 0) {

    accountid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.accountid_);
  }
  if (from.name().size() > 0) {

    name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  if (from.mobilephone().size() > 0) {

    mobilephone_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.mobilephone_);
  }
  if (from.email().size() > 0) {

    email_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.email_);
  }
  if (from.pwd().size() > 0) {

    pwd_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.pwd_);
  }
  if (from.sex() != 0) {
    set_sex(from.sex());
  }
}

void Register_CS::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:protobufMsg.Register_CS)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Register_CS::CopyFrom(const Register_CS& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobufMsg.Register_CS)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Register_CS::IsInitialized() const {
  return true;
}

void Register_CS::Swap(Register_CS* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Register_CS::InternalSwap(Register_CS* other) {
  using std::swap;
  accountid_.Swap(&other->accountid_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  name_.Swap(&other->name_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  mobilephone_.Swap(&other->mobilephone_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  email_.Swap(&other->email_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  pwd_.Swap(&other->pwd_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(sex_, other->sex_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata Register_CS::GetMetadata() const {
  protobuf_register_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_register_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void Register_SC::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Register_SC::kCodeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Register_SC::Register_SC()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_register_2eproto::scc_info_Register_SC.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:protobufMsg.Register_SC)
}
Register_SC::Register_SC(const Register_SC& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  code_ = from.code_;
  // @@protoc_insertion_point(copy_constructor:protobufMsg.Register_SC)
}

void Register_SC::SharedCtor() {
  code_ = 0;
}

Register_SC::~Register_SC() {
  // @@protoc_insertion_point(destructor:protobufMsg.Register_SC)
  SharedDtor();
}

void Register_SC::SharedDtor() {
}

void Register_SC::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* Register_SC::descriptor() {
  ::protobuf_register_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_register_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Register_SC& Register_SC::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_register_2eproto::scc_info_Register_SC.base);
  return *internal_default_instance();
}


void Register_SC::Clear() {
// @@protoc_insertion_point(message_clear_start:protobufMsg.Register_SC)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  code_ = 0;
  _internal_metadata_.Clear();
}

bool Register_SC::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:protobufMsg.Register_SC)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 code = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &code_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:protobufMsg.Register_SC)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:protobufMsg.Register_SC)
  return false;
#undef DO_
}

void Register_SC::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:protobufMsg.Register_SC)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 code = 1;
  if (this->code() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->code(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:protobufMsg.Register_SC)
}

::google::protobuf::uint8* Register_SC::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:protobufMsg.Register_SC)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 code = 1;
  if (this->code() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->code(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protobufMsg.Register_SC)
  return target;
}

size_t Register_SC::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobufMsg.Register_SC)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // int32 code = 1;
  if (this->code() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->code());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Register_SC::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:protobufMsg.Register_SC)
  GOOGLE_DCHECK_NE(&from, this);
  const Register_SC* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Register_SC>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:protobufMsg.Register_SC)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:protobufMsg.Register_SC)
    MergeFrom(*source);
  }
}

void Register_SC::MergeFrom(const Register_SC& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:protobufMsg.Register_SC)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.code() != 0) {
    set_code(from.code());
  }
}

void Register_SC::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:protobufMsg.Register_SC)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Register_SC::CopyFrom(const Register_SC& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobufMsg.Register_SC)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Register_SC::IsInitialized() const {
  return true;
}

void Register_SC::Swap(Register_SC* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Register_SC::InternalSwap(Register_SC* other) {
  using std::swap;
  swap(code_, other->code_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata Register_SC::GetMetadata() const {
  protobuf_register_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_register_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace protobufMsg
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::protobufMsg::Register_CS* Arena::CreateMaybeMessage< ::protobufMsg::Register_CS >(Arena* arena) {
  return Arena::CreateInternal< ::protobufMsg::Register_CS >(arena);
}
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::protobufMsg::Register_SC* Arena::CreateMaybeMessage< ::protobufMsg::Register_SC >(Arena* arena) {
  return Arena::CreateInternal< ::protobufMsg::Register_SC >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
