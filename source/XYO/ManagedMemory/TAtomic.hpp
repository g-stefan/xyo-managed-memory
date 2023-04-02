// Managed Memory
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TATOMIC_HPP
#define XYO_MANAGEDMEMORY_TATOMIC_HPP

#ifndef XYO_MANAGEDMEMORY_DEPENDENCY_HPP
#	include <XYO/ManagedMemory/Dependency.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	class TAtomic {
		protected:
#ifdef XYO_MULTI_THREAD
			std::atomic<T> value;
#endif
#ifdef XYO_SINGLE_THREAD
			T value;
#endif

		public:
#ifdef XYO_MULTI_THREAD
			static const bool isAtomic = true;
#endif
#ifdef XYO_SINGLE_THREAD
			static const bool isAtomic = false;
#endif

			inline TAtomic(){};

			inline void set(const T &value_) {
#ifdef XYO_MULTI_THREAD
				value.store(value_, std::memory_order_relaxed);
#endif
#ifdef XYO_SINGLE_THREAD
				value = value_;
#endif
			};

			inline void set(T &&value_) {
#ifdef XYO_MULTI_THREAD
				value.store(value_, std::memory_order_relaxed);
#endif
#ifdef XYO_SINGLE_THREAD
				value = std::move(value_);
#endif
			};

			inline T get() const {
#ifdef XYO_MULTI_THREAD
				return value.load(std::memory_order_relaxed);
#endif
#ifdef XYO_SINGLE_THREAD
				return value;
#endif
			};

			inline TAtomic(const TAtomic &value_) {
				set(value_.get());
			};

			inline TAtomic(TAtomic &&value_) {
				set(value_.get());
			};

			inline TAtomic &operator=(const TAtomic &value_) {
				set(value_.get());
			};

			inline TAtomic &operator=(TAtomic &&value_) {
				set(value_.get());
			};

			inline TAtomic(const T &value_) {
				set(value_);
			};

			inline TAtomic(T &&value_) {
				set(value_);
			};

			inline TAtomic &operator=(const T &value_) {
				set(value_);
				return *this;
			};

			inline TAtomic &operator=(T &&value_) {
				set(value_);
				return *this;
			};

			inline operator T() const {
				return get();
			};
	};
};

#endif
