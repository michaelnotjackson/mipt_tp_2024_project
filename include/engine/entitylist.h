#pragma once

#include <string>

#include "entity.h"

class CEntityNode {
 public:
  IBaseEntity* entity = nullptr;
  CEntityNode* next = nullptr;
  CEntityNode* prev = nullptr;
  int idx;

 public:

  ~CEntityNode();
};

class CEntityList {
 private:
  CEntityNode* head = nullptr;
  CEntityNode* last = nullptr;

 public:
  int highest_ent;  // Index of the last entity
  int ent_count;    // Count of existing entities

  std::map<void*, bool> deleted;

 public:
  void Insert(IBaseEntity* ent);
  void RemoveByIndex(int idx);

  IBaseEntity* GetByIndex(int idx);

  IBaseEntity* GetByPos(const SDL_Rect& pos);

  int GetIndByPos(const SDL_Rect& pos);

  CEntityNode* GetHead();

  ~CEntityList();

  template <bool isConst>
  class Iterator {
   private:
    CEntityNode* node_;
   public:
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef IBaseEntity* value_type;
    typedef ptrdiff_t difference_type;
    typedef value_type* pointer;
    typedef value_type& reference;

    Iterator(): node_(nullptr) {}
    Iterator(const Iterator& oth): node_(oth.node_) {}
    Iterator(CEntityNode* ptr): node_(ptr) {}

    Iterator& operator++() {
      node_ = node_->next;
      return *this;
    }
    Iterator operator++(int) {
      auto copy(*this);
      operator++();
      return copy;
    }

    Iterator& operator--() {
      node_ = node_->prev;
      return *this;
    }
    Iterator operator--(int) {
      auto copy(*this);
      operator--();
      return copy;
    }

    pointer operator->() {
      return &node_->entity;
    }

    reference operator*() {
      return node_->entity;
    }

    bool operator==(const Iterator& oth) const {
      return node_ == oth.node_;
    }

    bool operator!=(const Iterator& oth) const {
      return node_ != oth.node_;
    }
  };

  typedef Iterator<false> iterator;
  typedef Iterator<true> const_iterator;


  iterator begin() {
    return iterator(head);
  }
  const_iterator cbegin() const {
    return const_iterator(head);
  }

  iterator end() {
    return iterator(last->next);
  }
  const_iterator cend() const {
    return const_iterator(last->next);
  };
};

extern CEntityList entity_list;