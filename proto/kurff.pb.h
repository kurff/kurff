// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: kurff.proto

#ifndef PROTOBUF_INCLUDED_kurff_2eproto
#define PROTOBUF_INCLUDED_kurff_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
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
#define PROTOBUF_INTERNAL_EXPORT_protobuf_kurff_2eproto 

namespace protobuf_kurff_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_kurff_2eproto
namespace kurff {
class Parameters;
class ParametersDefaultTypeInternal;
extern ParametersDefaultTypeInternal _Parameters_default_instance_;
class bounder;
class bounderDefaultTypeInternal;
extern bounderDefaultTypeInternal _bounder_default_instance_;
}  // namespace kurff
namespace google {
namespace protobuf {
template<> ::kurff::Parameters* Arena::CreateMaybeMessage<::kurff::Parameters>(Arena*);
template<> ::kurff::bounder* Arena::CreateMaybeMessage<::kurff::bounder>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace kurff {

// ===================================================================

class bounder : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:kurff.bounder) */ {
 public:
  bounder();
  virtual ~bounder();

  bounder(const bounder& from);

  inline bounder& operator=(const bounder& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  bounder(bounder&& from) noexcept
    : bounder() {
    *this = ::std::move(from);
  }

  inline bounder& operator=(bounder&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const bounder& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const bounder* internal_default_instance() {
    return reinterpret_cast<const bounder*>(
               &_bounder_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(bounder* other);
  friend void swap(bounder& a, bounder& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline bounder* New() const final {
    return CreateMaybeMessage<bounder>(NULL);
  }

  bounder* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<bounder>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const bounder& from);
  void MergeFrom(const bounder& from);
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
  void InternalSwap(bounder* other);
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

  // required float upper = 1 [default = 0];
  bool has_upper() const;
  void clear_upper();
  static const int kUpperFieldNumber = 1;
  float upper() const;
  void set_upper(float value);

  // required float lower = 2 [default = 0];
  bool has_lower() const;
  void clear_lower();
  static const int kLowerFieldNumber = 2;
  float lower() const;
  void set_lower(float value);

  // @@protoc_insertion_point(class_scope:kurff.bounder)
 private:
  void set_has_upper();
  void clear_has_upper();
  void set_has_lower();
  void clear_has_lower();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  float upper_;
  float lower_;
  friend struct ::protobuf_kurff_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Parameters : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:kurff.Parameters) */ {
 public:
  Parameters();
  virtual ~Parameters();

  Parameters(const Parameters& from);

  inline Parameters& operator=(const Parameters& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Parameters(Parameters&& from) noexcept
    : Parameters() {
    *this = ::std::move(from);
  }

  inline Parameters& operator=(Parameters&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Parameters& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Parameters* internal_default_instance() {
    return reinterpret_cast<const Parameters*>(
               &_Parameters_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Parameters* other);
  friend void swap(Parameters& a, Parameters& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Parameters* New() const final {
    return CreateMaybeMessage<Parameters>(NULL);
  }

  Parameters* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Parameters>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Parameters& from);
  void MergeFrom(const Parameters& from);
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
  void InternalSwap(Parameters* other);
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

  // required .kurff.bounder mean = 1;
  bool has_mean() const;
  void clear_mean();
  static const int kMeanFieldNumber = 1;
  private:
  const ::kurff::bounder& _internal_mean() const;
  public:
  const ::kurff::bounder& mean() const;
  ::kurff::bounder* release_mean();
  ::kurff::bounder* mutable_mean();
  void set_allocated_mean(::kurff::bounder* mean);

  // required .kurff.bounder std = 2;
  bool has_std() const;
  void clear_std();
  static const int kStdFieldNumber = 2;
  private:
  const ::kurff::bounder& _internal_std() const;
  public:
  const ::kurff::bounder& std() const;
  ::kurff::bounder* release_std();
  ::kurff::bounder* mutable_std();
  void set_allocated_std(::kurff::bounder* std);

  // required .kurff.bounder angle = 3;
  bool has_angle() const;
  void clear_angle();
  static const int kAngleFieldNumber = 3;
  private:
  const ::kurff::bounder& _internal_angle() const;
  public:
  const ::kurff::bounder& angle() const;
  ::kurff::bounder* release_angle();
  ::kurff::bounder* mutable_angle();
  void set_allocated_angle(::kurff::bounder* angle);

  // required .kurff.bounder scale = 4;
  bool has_scale() const;
  void clear_scale();
  static const int kScaleFieldNumber = 4;
  private:
  const ::kurff::bounder& _internal_scale() const;
  public:
  const ::kurff::bounder& scale() const;
  ::kurff::bounder* release_scale();
  ::kurff::bounder* mutable_scale();
  void set_allocated_scale(::kurff::bounder* scale);

  // @@protoc_insertion_point(class_scope:kurff.Parameters)
 private:
  void set_has_mean();
  void clear_has_mean();
  void set_has_std();
  void clear_has_std();
  void set_has_angle();
  void clear_has_angle();
  void set_has_scale();
  void clear_has_scale();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::kurff::bounder* mean_;
  ::kurff::bounder* std_;
  ::kurff::bounder* angle_;
  ::kurff::bounder* scale_;
  friend struct ::protobuf_kurff_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// bounder

// required float upper = 1 [default = 0];
inline bool bounder::has_upper() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void bounder::set_has_upper() {
  _has_bits_[0] |= 0x00000001u;
}
inline void bounder::clear_has_upper() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void bounder::clear_upper() {
  upper_ = 0;
  clear_has_upper();
}
inline float bounder::upper() const {
  // @@protoc_insertion_point(field_get:kurff.bounder.upper)
  return upper_;
}
inline void bounder::set_upper(float value) {
  set_has_upper();
  upper_ = value;
  // @@protoc_insertion_point(field_set:kurff.bounder.upper)
}

// required float lower = 2 [default = 0];
inline bool bounder::has_lower() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void bounder::set_has_lower() {
  _has_bits_[0] |= 0x00000002u;
}
inline void bounder::clear_has_lower() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void bounder::clear_lower() {
  lower_ = 0;
  clear_has_lower();
}
inline float bounder::lower() const {
  // @@protoc_insertion_point(field_get:kurff.bounder.lower)
  return lower_;
}
inline void bounder::set_lower(float value) {
  set_has_lower();
  lower_ = value;
  // @@protoc_insertion_point(field_set:kurff.bounder.lower)
}

// -------------------------------------------------------------------

// Parameters

// required .kurff.bounder mean = 1;
inline bool Parameters::has_mean() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Parameters::set_has_mean() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Parameters::clear_has_mean() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Parameters::clear_mean() {
  if (mean_ != NULL) mean_->Clear();
  clear_has_mean();
}
inline const ::kurff::bounder& Parameters::_internal_mean() const {
  return *mean_;
}
inline const ::kurff::bounder& Parameters::mean() const {
  const ::kurff::bounder* p = mean_;
  // @@protoc_insertion_point(field_get:kurff.Parameters.mean)
  return p != NULL ? *p : *reinterpret_cast<const ::kurff::bounder*>(
      &::kurff::_bounder_default_instance_);
}
inline ::kurff::bounder* Parameters::release_mean() {
  // @@protoc_insertion_point(field_release:kurff.Parameters.mean)
  clear_has_mean();
  ::kurff::bounder* temp = mean_;
  mean_ = NULL;
  return temp;
}
inline ::kurff::bounder* Parameters::mutable_mean() {
  set_has_mean();
  if (mean_ == NULL) {
    auto* p = CreateMaybeMessage<::kurff::bounder>(GetArenaNoVirtual());
    mean_ = p;
  }
  // @@protoc_insertion_point(field_mutable:kurff.Parameters.mean)
  return mean_;
}
inline void Parameters::set_allocated_mean(::kurff::bounder* mean) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete mean_;
  }
  if (mean) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      mean = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, mean, submessage_arena);
    }
    set_has_mean();
  } else {
    clear_has_mean();
  }
  mean_ = mean;
  // @@protoc_insertion_point(field_set_allocated:kurff.Parameters.mean)
}

// required .kurff.bounder std = 2;
inline bool Parameters::has_std() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Parameters::set_has_std() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Parameters::clear_has_std() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Parameters::clear_std() {
  if (std_ != NULL) std_->Clear();
  clear_has_std();
}
inline const ::kurff::bounder& Parameters::_internal_std() const {
  return *std_;
}
inline const ::kurff::bounder& Parameters::std() const {
  const ::kurff::bounder* p = std_;
  // @@protoc_insertion_point(field_get:kurff.Parameters.std)
  return p != NULL ? *p : *reinterpret_cast<const ::kurff::bounder*>(
      &::kurff::_bounder_default_instance_);
}
inline ::kurff::bounder* Parameters::release_std() {
  // @@protoc_insertion_point(field_release:kurff.Parameters.std)
  clear_has_std();
  ::kurff::bounder* temp = std_;
  std_ = NULL;
  return temp;
}
inline ::kurff::bounder* Parameters::mutable_std() {
  set_has_std();
  if (std_ == NULL) {
    auto* p = CreateMaybeMessage<::kurff::bounder>(GetArenaNoVirtual());
    std_ = p;
  }
  // @@protoc_insertion_point(field_mutable:kurff.Parameters.std)
  return std_;
}
inline void Parameters::set_allocated_std(::kurff::bounder* std) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete std_;
  }
  if (std) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      std = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, std, submessage_arena);
    }
    set_has_std();
  } else {
    clear_has_std();
  }
  std_ = std;
  // @@protoc_insertion_point(field_set_allocated:kurff.Parameters.std)
}

// required .kurff.bounder angle = 3;
inline bool Parameters::has_angle() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void Parameters::set_has_angle() {
  _has_bits_[0] |= 0x00000004u;
}
inline void Parameters::clear_has_angle() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void Parameters::clear_angle() {
  if (angle_ != NULL) angle_->Clear();
  clear_has_angle();
}
inline const ::kurff::bounder& Parameters::_internal_angle() const {
  return *angle_;
}
inline const ::kurff::bounder& Parameters::angle() const {
  const ::kurff::bounder* p = angle_;
  // @@protoc_insertion_point(field_get:kurff.Parameters.angle)
  return p != NULL ? *p : *reinterpret_cast<const ::kurff::bounder*>(
      &::kurff::_bounder_default_instance_);
}
inline ::kurff::bounder* Parameters::release_angle() {
  // @@protoc_insertion_point(field_release:kurff.Parameters.angle)
  clear_has_angle();
  ::kurff::bounder* temp = angle_;
  angle_ = NULL;
  return temp;
}
inline ::kurff::bounder* Parameters::mutable_angle() {
  set_has_angle();
  if (angle_ == NULL) {
    auto* p = CreateMaybeMessage<::kurff::bounder>(GetArenaNoVirtual());
    angle_ = p;
  }
  // @@protoc_insertion_point(field_mutable:kurff.Parameters.angle)
  return angle_;
}
inline void Parameters::set_allocated_angle(::kurff::bounder* angle) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete angle_;
  }
  if (angle) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      angle = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, angle, submessage_arena);
    }
    set_has_angle();
  } else {
    clear_has_angle();
  }
  angle_ = angle;
  // @@protoc_insertion_point(field_set_allocated:kurff.Parameters.angle)
}

// required .kurff.bounder scale = 4;
inline bool Parameters::has_scale() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void Parameters::set_has_scale() {
  _has_bits_[0] |= 0x00000008u;
}
inline void Parameters::clear_has_scale() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void Parameters::clear_scale() {
  if (scale_ != NULL) scale_->Clear();
  clear_has_scale();
}
inline const ::kurff::bounder& Parameters::_internal_scale() const {
  return *scale_;
}
inline const ::kurff::bounder& Parameters::scale() const {
  const ::kurff::bounder* p = scale_;
  // @@protoc_insertion_point(field_get:kurff.Parameters.scale)
  return p != NULL ? *p : *reinterpret_cast<const ::kurff::bounder*>(
      &::kurff::_bounder_default_instance_);
}
inline ::kurff::bounder* Parameters::release_scale() {
  // @@protoc_insertion_point(field_release:kurff.Parameters.scale)
  clear_has_scale();
  ::kurff::bounder* temp = scale_;
  scale_ = NULL;
  return temp;
}
inline ::kurff::bounder* Parameters::mutable_scale() {
  set_has_scale();
  if (scale_ == NULL) {
    auto* p = CreateMaybeMessage<::kurff::bounder>(GetArenaNoVirtual());
    scale_ = p;
  }
  // @@protoc_insertion_point(field_mutable:kurff.Parameters.scale)
  return scale_;
}
inline void Parameters::set_allocated_scale(::kurff::bounder* scale) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete scale_;
  }
  if (scale) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      scale = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, scale, submessage_arena);
    }
    set_has_scale();
  } else {
    clear_has_scale();
  }
  scale_ = scale;
  // @@protoc_insertion_point(field_set_allocated:kurff.Parameters.scale)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace kurff

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_kurff_2eproto