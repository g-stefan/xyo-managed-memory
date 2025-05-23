// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TIFHASACTIVEFINALIZER_HPP
#define XYO_MANAGEDMEMORY_TIFHASACTIVEFINALIZER_HPP

#ifndef XYO_MANAGEDMEMORY_TGETCLASSOFMEMBER_HPP
#	include <XYO/ManagedMemory/TGetClassOfMember.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	class THasActiveFinalizer {
		protected:
			template <typename U, void (U::*)()>
			struct TCheckMember;

			template <typename U>
			static char TTestMember(TCheckMember<U, &U::activeFinalizer> *);

			template <typename U>
			static int TTestMember(...);

			template <typename U>
			struct THasMember {
					static const bool value = sizeof(TTestMember<U>(nullptr)) == sizeof(char);
			};

			template <typename U>
			static char TTestBaseMember(decltype(TGetClassOfMember(&U::activeFinalizer)) *);

			template <typename U>
			static int TTestBaseMember(...);

			template <typename U>
			struct THasBaseMember {
					static const bool value = sizeof(TTestBaseMember<U>(nullptr)) == sizeof(char);
			};

			template <typename U, bool hasBase>
			struct TProcessBaseMember {
					static const bool value = false;
			};

			template <typename U>
			class TProcessBaseMember<U, true> {
					static const bool value = THasMember<decltype(TGetClassOfMember(&U::activeFinalizer))>::value;
			};

		public:
			static const bool value = THasMember<T>::value | TProcessBaseMember<T, THasBaseMember<T>::value>::value;
	};

	template <typename T, bool hasActiveFinalizer>
	struct TIfHasActiveFinalizerBase {

			static inline void activeFinalizer(T *){};

			static inline void activeFinalizerArray(T *this_, size_t length){};
	};

	template <typename T>
	struct TIfHasActiveFinalizerBase<T, true> {

			static inline void activeFinalizer(T *this_) {
				this_->activeFinalizer();
			};

			static inline void activeFinalizerArray(T *this_, size_t length) {
				size_t k;
				for (k = 0; k < length; ++k) {
					this_[k].activeFinalizer();
				};
			};
	};

	template <typename T>
	struct TIfHasActiveFinalizer : public TIfHasActiveFinalizerBase<T, THasActiveFinalizer<T>::value> {
	};

};

#endif
