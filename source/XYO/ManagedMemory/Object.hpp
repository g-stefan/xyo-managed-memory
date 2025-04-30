// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_OBJECT_HPP
#define XYO_MANAGEDMEMORY_OBJECT_HPP

#ifndef XYO_MANAGEDMEMORY_DELETEMEMORY_HPP
#	include <XYO/ManagedMemory/DeleteMemory.hpp>
#endif

#ifndef XYO_MANAGEDMEMORY_POINTERX_HPP
#	include <XYO/ManagedMemory/PointerX.hpp>
#endif

namespace XYO::ManagedMemory {

	class Object {
			XYO_PLATFORM_DISALLOW_COPY_ASSIGN_MOVE(Object);

		protected:
#ifdef XYO_MANAGEDMEMORY_64BIT
			int64_t referenceCounter_;
#else
			int32_t referenceCounter_;
#endif
			DeleteMemory deleteMemory_;
			void *memoryThis_;
			PointerX *pointerXHead_;

			void XYO_MANAGEDMEMORY_EXPORT referenceMarkAndSweep_();
			bool XYO_MANAGEDMEMORY_EXPORT referenceMarkIsDynamic_();
			bool XYO_MANAGEDMEMORY_EXPORT referenceMarkReset_();

		public:
			XYO_MANAGEDMEMORY_EXPORT Object();
			virtual XYO_MANAGEDMEMORY_EXPORT ~Object();

			bool referenceMark_;
			bool referenceIsBranch_;

			inline void incReferenceCount() {
				++referenceCounter_;
			};

			void XYO_MANAGEDMEMORY_EXPORT decReferenceCount();

			inline void setDeleteMemory(DeleteMemory deleteMemory, void *memoryThis) {
				deleteMemory_ = deleteMemory;
				memoryThis_ = memoryThis;
			};

			void XYO_MANAGEDMEMORY_EXPORT addPointerX(PointerX *value);
			void XYO_MANAGEDMEMORY_EXPORT removePointerX(PointerX *value);
			void XYO_MANAGEDMEMORY_EXPORT transferPointerX(PointerX *value, const Object *object, const void *object_);

			inline void decReferenceCountExecutive() {
				--referenceCounter_;
			};

			inline bool hasOneReference() const {
				if ((referenceCounter_ <= 1) && (pointerXHead_ == nullptr)) {
					return true;
				};
				if ((referenceCounter_ <= 0) && (pointerXHead_ != nullptr)) {
					if (pointerXHead_->next == nullptr) {
						return true;
					};
				};
				return false;
			};
	};

};

#endif
