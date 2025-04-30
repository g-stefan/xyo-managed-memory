// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#include <XYO/ManagedMemory/Object.hpp>
#include <XYO/ManagedMemory/TXList2.hpp>

namespace XYO::ManagedMemory {

	Object::Object() {
		referenceCounter_ = 0;
		deleteMemory_ = nullptr;
		pointerXHead_ = nullptr;
		referenceMark_ = false;
		referenceIsBranch_ = false;
	};

	Object::~Object(){};

	void Object::decReferenceCount() {
		--referenceCounter_;
		if (referenceCounter_ <= 0) {
			referenceCounter_ = 0;
			if (pointerXHead_ == nullptr) {
				if (deleteMemory_) {
					(*deleteMemory_)(memoryThis_);
				};
				return;
			};
			if (referenceIsBranch_) {
				referenceMarkAndSweep_();
			};
			return;
		};
	};

	void Object::addPointerX(struct PointerX *value) {
		TXList2<PointerX>::push(pointerXHead_, value);
	};

	void Object::removePointerX(struct PointerX *value) {
		value->object = nullptr;

		TXList2<PointerX>::extract(pointerXHead_, value);

		if (pointerXHead_ == nullptr) {
			if (referenceCounter_ <= 0) {
				referenceCounter_ = 0;
				if (deleteMemory_) {
					(*deleteMemory_)(memoryThis_);
				};
			};
			return;
		};

		if (referenceCounter_ <= 0) {
			referenceCounter_ = 0;
			if (referenceIsBranch_) {
				referenceMarkAndSweep_();
			};
		};
	};

	void Object::transferPointerX(struct PointerX *value, const Object *object, const void *object_) {
		if (this == object) {
			return;
		};

		TXList2<PointerX>::extract(pointerXHead_, value);

		value->object = const_cast<void *>(object_);

		if (object) {
			(const_cast<Object *>(object))->addPointerX(value);
		};

		if (pointerXHead_ == nullptr) {
			if (referenceCounter_ <= 0) {
				referenceCounter_ = 0;
				if (deleteMemory_) {
					(*deleteMemory_)(memoryThis_);
				};
			};
			return;
		};

		if (referenceCounter_ <= 0) {
			referenceCounter_ = 0;
			if (referenceIsBranch_) {
				referenceMarkAndSweep_();
			};
		};
	};

	void Object::referenceMarkAndSweep_() {

		if (referenceMarkIsDynamic_()) {
			referenceMarkReset_();

			//
			// All pointers are dynamic - reclaim
			//
			struct PointerX *index;
			for (index = pointerXHead_; index; index = index->next) {
				index->object = nullptr;
			};
			pointerXHead_ = nullptr;
			if (deleteMemory_) {
				(*deleteMemory_)(memoryThis_);
			};
			return;
		};
		referenceMarkReset_();
	};

	bool Object::referenceMarkIsDynamic_() {
		struct PointerX *index;

		referenceMark_ = true;
		for (index = pointerXHead_; index; index = index->next) {
			if (index->link) {
				if (!index->link->deleteMemory_) {
					return false;
				};
				if (index->link->referenceCounter_) {
					return false;
				};
				if (index->link->referenceMark_) {
					continue;
				};
				if (!index->link->referenceMarkIsDynamic_()) {
					return false;
				};
			};
		};
		return true;
	};

	bool Object::referenceMarkReset_() {
		struct PointerX *index;

		referenceMark_ = false;
		for (index = pointerXHead_; index; index = index->next) {
			if (index->link) {
				if (!index->link->deleteMemory_) {
					return false;
				};
				if (index->link->referenceCounter_) {
					return false;
				};
				if (!index->link->referenceMark_) {
					continue;
				};
				if (!index->link->referenceMarkReset_()) {
					return false;
				};
			};
		};
		return true;
	};

};
