#pragma once
namespace SRE {

	class HardwareBuffer {

	public:
		virtual ~HardwareBuffer() {};
	public:
		enum Usage
		{
			/** Static buffer which the application rarely modifies once created. Modifying
			the contents of this buffer will involve a performance hit.
			*/
			HBU_STATIC = 1,
			/** Indicates the application would like to modify this buffer with the CPU
			fairly often.
			Buffers created with this flag will typically end up in AGP memory rather
			than video memory.
			*/
			HBU_DYNAMIC = 2,
			/** Indicates the application will never read the contents of the buffer back,
			it will only ever write data. Locking a buffer with this flag will ALWAYS
			return a pointer to new, blank memory rather than the memory associated
			with the contents of the buffer; this avoids DMA stalls because you can
			write to a new memory area while the previous one is being used.
			*/
			HBU_WRITE_ONLY = 4,
			/** Indicates that the application will be refilling the contents
			of the buffer regularly (not just updating, but generating the
			contents from scratch), and therefore does not mind if the contents
			of the buffer are lost somehow and need to be recreated. This
			allows and additional level of optimisation on the buffer.
			This option only really makes sense when combined with
			HBU_DYNAMIC_WRITE_ONLY.
			*/
			HBU_DISCARDABLE = 8,
			/// Combination of HBU_STATIC and HBU_WRITE_ONLY
			HBU_STATIC_WRITE_ONLY = 5,
			/** Combination of HBU_DYNAMIC and HBU_WRITE_ONLY. If you use
			this, strongly consider using HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE
			instead if you update the entire contents of the buffer very
			regularly.
			*/
			HBU_DYNAMIC_WRITE_ONLY = 6,
			/// Combination of HBU_DYNAMIC, HBU_WRITE_ONLY and HBU_DISCARDABLE
			HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE = 14


		};
		/// Locking options
		enum LockOptions
		{
			/** Normal mode, ie allows read/write and contents are preserved. */
			HBL_NORMAL,
			/** Discards the <em>entire</em> buffer while locking; this allows optimisation to be
			performed because synchronisation issues are relaxed. Only allowed on buffers
			created with the HBU_DYNAMIC flag.
			*/
			HBL_DISCARD,
			/** Lock the buffer for reading only. Not allowed in buffers which are created with HBU_WRITE_ONLY.
			Mandatory on static buffers, i.e. those created without the HBU_DYNAMIC flag.
			*/
			HBL_READ_ONLY,
			/** As HBL_DISCARD, except the application guarantees not to overwrite any
			region of the buffer which has already been used in this frame, can allow
			some optimisation on some APIs. */
			HBL_NO_OVERWRITE,
			/** Lock the buffer for writing only.*/
			HBL_WRITE_ONLY

		};
	public:
	
		virtual void*	lock(unsigned int offset, unsigned int length, LockOptions options) = 0;
		virtual void*	lock(LockOptions options) = 0;
		virtual void	unlock(void) = 0;

		virtual void	readData(unsigned int offset, unsigned int length, void* dest) = 0;
		virtual void	writeData(unsigned int offset, unsigned int length, const void* source,	bool discardWholeBuffer = false) = 0;

		//virtual void	copyData(HardwareBuffer& src_buffer_, unsigned int src_offset, unsigned int dst_offset, unsigned int length, bool discardWholeBuffer = false) = 0;
		//virtual void	copyData(HardwareBuffer& src_buffer) = 0;

		virtual unsigned int	getSizeInBytes(void) const = 0;
		virtual Usage	getUsage(void) const = 0;

		virtual bool    isLocked(void) const = 0;
		virtual bool	isUseShadowBuffer(void) const = 0;

		virtual void    upload(void) = 0;
	};

	
}