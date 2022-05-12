#pragma once

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "folly/FBString.h"

struct IDCard {
  folly::fbstring guid;
  folly::fbstring name;
  folly::fbstring version;
  folly::fbstring description;

  IDCard() {
    guid = GenerateUUID();
    name = "";
    version = "v1.0.0";
    description = "";
  }

  explicit IDCard(const folly::fbstring &name) {
    this->name = name;
  }

  IDCard(const folly::fbstring &guid,
         const folly::fbstring &name,
         const folly::fbstring &version,
         const folly::fbstring &description) {
    this->guid = guid;
    this->name = name;
    this->version = version;
    this->description = description;
  }

  IDCard(const IDCard &id_card) {
    guid = id_card.guid;
    name = id_card.name;
    version = id_card.version;
    description = id_card.description;
  }

  IDCard &operator=(const IDCard &id_card) = default;

  bool operator==(const IDCard &id_card) const {
    return name == id_card.name
        && guid == id_card.guid
        && version == id_card.version;
  }

  bool operator!=(const IDCard &id_card) const {
    return !(*this == id_card);
  }

  static folly::fbstring GenerateUUID() {
    auto uuid = boost::uuids::random_generator()();
    folly::fbstring uuid_str = boost::uuids::to_string(uuid);
    return uuid_str;
  }
};

class IDCardWrapper {
 public:
  IDCardWrapper() = default;
  virtual ~IDCardWrapper() = default;

  inline void SetGUID(const folly::fbstring &guid) {
    id_card_.guid = guid;
  }

  inline folly::fbstring GetGUID() const {
    return id_card_.guid;
  }

  inline void SetName(const folly::fbstring &name) {
    id_card_.name = name;
  }

  inline folly::fbstring GetName() const {
    return id_card_.name;
  }

  inline void SetVersion(const folly::fbstring &version) {
    id_card_.version = version;
  }

  inline folly::fbstring GetVersion() const {
    return id_card_.version;
  }

  inline void SetDescription(const folly::fbstring &description) {
    id_card_.description = description;
  }

  inline folly::fbstring GetDescription() const {
    return id_card_.description;
  }

  inline void SetIDCard(const IDCard &id_card) {
    id_card_ = id_card;
  }

  inline IDCard GetIDCard() const {
    return id_card_;
  }

 private:
  IDCard id_card_;
};
