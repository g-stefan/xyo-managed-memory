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

#ifdef XYO_MULTI_THREAD
namespace XYO::ManagedMemory {

	template <typename T>
	class TAtomic {
		protected:
			std::atomic<T> value;

		public:
			static const bool isAtomic = true;

			inline TAtomic(){};

			inline void set(const T &value_) {
				value.store(value_, std::memory_order_relaxed);
			};

			inline void set(T &&value_) {
				value.store(value_, std::memory_order_relaxed);
			};

			inline T get() const {
				return value.load(std::memory_order_relaxed);
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

#ifdef XYO_SINGLE_THREAD
namespace XYO::ManagedMemory {

	template <typename T>
	class TAtomic {
		protected:
			T value;

		public:
			static const bool isAtomic = false;

			inline TAtomic(){};

			inline void set(const T &value_) {
				value = value_;
			};

			inline void set(T &&value_) {
				value = std::move(value_);
			};

			inline T get() const {
				return value;
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

#endif
