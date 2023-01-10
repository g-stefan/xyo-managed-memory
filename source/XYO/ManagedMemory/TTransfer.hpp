// Managed Memory
// Copyright (c) 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// MIT License (MIT) <http://opensource.org/licenses/MIT>
// SPDX-FileCopyrightText: 2016-2023 Grigore Stefan <g_stefan@yahoo.com>
// SPDX-License-Identifier: MIT

#ifndef XYO_MANAGEDMEMORY_TTRANSFER_HPP
#define XYO_MANAGEDMEMORY_TTRANSFER_HPP

namespace XYO::ManagedMemory {

	struct TTransferNone;

	template <typename T, typename X = TTransferNone>
	struct TTransfer {
			static inline TTransfer<T> *transfer(const T *value_) {
				return reinterpret_cast<TTransfer<T> *>(const_cast<T *>(value_));
			};

			inline T *operator->() {
				return reinterpret_cast<T *>(this);
			};

			inline T *value() {
				return reinterpret_cast<T *>(this);
			};

			static inline TTransfer<T> *cast(TTransfer<X> *value_) {
				return reinterpret_cast<TTransfer<T> *>(static_cast<T *>(reinterpret_cast<X *>(value_)));
			};
	};

};

#endif
