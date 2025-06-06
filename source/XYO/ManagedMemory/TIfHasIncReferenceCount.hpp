// Managed Memory
// Copyright (c) 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2025 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TIFHASINCREFERENCECOUNT_HPP
#define XYO_MANAGEDMEMORY_TIFHASINCREFERENCECOUNT_HPP

#ifndef XYO__MANAGEDMEMORY_TGETCLASSOFMEMBER_HPP
#	include <XYO/ManagedMemory/TGetClassOfMember.hpp>
#endif

namespace XYO::ManagedMemory {

	template <typename T>
	class THasIncReferenceCount {
		protected:
			template <typename U, void (U::*)()>
			struct TCheckMember;

			template <typename U>
			static char TTestMember(TCheckMember<U, &U::incReferenceCount> *);

			template <typename U>
			static int TTestMember(...);

			template <typename U>
			struct THasMember {
					static const bool value = sizeof(TTestMember<U>(nullptr)) == sizeof(char);
			};

			template <typename U>
			static char TTestBaseMember(decltype(TGetClassOfMember(&U::incReferenceCount)) *);

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
			struct TProcessBaseMember<U, true> {
					static const bool value = THasMember<decltype(TGetClassOfMember(&U::incReferenceCount))>::value;
			};

		public:
			static const bool value = THasMember<T>::value | TProcessBaseMember<T, THasBaseMember<T>::value>::value;
	};

	template <typename T, bool hasIncReferenceCount>
	struct TIfHasIncReferenceCountBase {
			static inline void incReferenceCount(T *){};
	};

	template <typename T>
	struct TIfHasIncReferenceCountBase<T, true> {
			static inline void incReferenceCount(T *this_) {
				this_->incReferenceCount();
			};
	};

	template <typename T>
	struct TIfHasIncReferenceCount : TIfHasIncReferenceCountBase<T, THasIncReferenceCount<T>::value> {
	};

};

#endif
