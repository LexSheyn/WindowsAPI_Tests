#pragma once

#include "TrickAPI.h"
#include "TrickPrimitiveTypes.h"

typedef enum TkStructureType
{
	  TK_STRUCTURE_TYPE_APPLICATION_CREATE_INFO
	, TK_STRUCTURE_TYPE_ENGINE_CREATE_INFO
	, TK_STRUCTURE_TYPE_MODULE_CREATE_INFO
	, TK_STRUCTURE_TYPE_WINDOW_CREATE_INFO
	, TK_STRUCTURE_TYPE_VULKAN_FRAMEBUFFER_CREATE_INFO
	, TK_STRUCTURE_TYPE_VULKAN_BUFFER_CREATE_INFO
	, TK_STRUCTURE_TYPE_VULKAN_SHADER_CREATE_INFO
	, TK_STRUCTURE_TYPE_VULKAN_WINDOW_CREATE_INFO
	, TK_STRUCTURE_TYPE_VULKAN_SWAPCHAIN_CREATE_INFO
	, TK_STRUCTURE_TYPE_VULKAN_OBJECT_GRAPHICS_PIPELINE_CREATE_INFO
	, TK_STRUCTURE_TYPE_LIST_CREATE_INFO
	, TK_STRUCTURE_TYPE_LIST_NODE_CREATE_INFO
	, TK_STRUCTURE_TYPE_QUEUE_CREATE_INFO
	, TK_STRUCTURE_TYPE_QUEUE_NODE_CREATE_INFO
	, TK_STRUCTURE_TYPE_STACK_CREATE_INFO
	, TK_STRUCTURE_TYPE_VECTOR_CREATE_INFO
	, TK_STRUCTURE_TYPE_MEMORY_BLOCK_STORAGE_CREATE_INFO
	, TK_STRUCTURE_TYPE_MEMORY_POOL_CREATE_INFO
	, TK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO
	, TK_STRUCTURE_TYPE_SIGNAL_CREATE_INFO
	, TK_STRUCTURE_TYPE_THREAD_LAUNCH_INFO
	, TK_STRUCTURE_TYPE_FILE_MONITOR_START_INFO
	, TK_STRUCTURE_TYPE_FILE_OPEN_INFO
	, TK_STRUCTURE_TYPE_LINEAR_ALLOCATOR_CREATE_INFO
	, TK_STRUCTURE_TYPE_LOGGER_INIT_INFO
	, TK_STRUCTURE_TYPE_TEXTURE_CREATE_INFO
	, TK_STRUCTURE_TYPE_MAX_ENUM = TK_INT32_MAX
} TkStructureType;

typedef enum TkResult
{
	  TK_SUCCESS                      = 0
	, TK_NOT_READY                    = 1
	, TK_TERMINATED                   = 2
	, TK_ABANDONED                    = 3
	, TK_TIMEOUT                      = 4
	, TK_SKIPPED                      = 5
	, TK_ERROR_INITIALIZATION_FAILED  = -1
	, TK_ERROR_ELEMENT_DUPLICATE      = -2
	, TK_ERROR_ELEMENT_NOT_PRESENT    = -3
	, TK_ERROR_MODULE_WINDOW_MISMATCH = -4
	, TK_ERROR_ACCESS_DENIED          = -5
	, TK_ERROR_OUT_OF_HOST_MEMORY     = -6
	, TK_ERROR_FILE_NOT_FOUND         = -7
	, TK_ERROR_PATH_NOT_FOUND         = -8
	, TK_ERROR_FILE_EXISTS            = -9
	, TK_ERROR_ALREADY_EXISTS         = -10
	, TK_ERROR_UNKNOWN                = -100
	, TK_ERROR_MAX_ENUM               = TK_INT32_MAX
} TkResult;

typedef struct TkMemoryRequirements
{
	tk_size_t      Size;
	tk_size_t      Alignment;
	tk_size_t      AlignedSize;
	tk_uint32_t    MemoryTypeBits;
} TkMemoryRequirements;

typedef enum TkSystemAllocationScope
{
	  TK_SYSTEM_ALLOCATION_SCOPE_OBJECT
	, TK_SYSTEM_ALLOCATION_SCOPE_ENUM_SIZE
	, TK_SYSTEM_ALLOCATION_SCOPE_MAX_ENUM = TK_INT32_MAX
} TkSystemAllocationScope;

typedef enum TkInternalAllocationType
{
	  TK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE
	, TK_INTERNAL_ALLOCATION_TYPE_ENUM_SIZE
	, TK_INTERNAL_ALLOCATION_TYPE_MAX_ENUM = TK_INT32_MAX
} TkInternalAllocationType;

typedef void* (TK_CALL *PFN_tkAllocationFunction)(
	void*                       p_Allocator,
	tk_size_t                      Size,
	tk_size_t                      Alignment,
	TkSystemAllocationScope     AllocationScope);

typedef void (TK_CALL *PFN_tkFreeFunction)(
	void*                       p_Allocator,
	void*                       p_Memory);

typedef void* (TK_CALL* PFN_tkReallocationFunction)(
	void*                       p_Allocator,
	void*                       p_Original,
	tk_size_t                      Size,
	tk_size_t                      Alignment,
	TkSystemAllocationScope     AllocationScope);

typedef void* (TK_CALL *PFN_tkIntenalAllocationNotification)(
	void*                       p_Allocator,
	tk_size_t                      Size,
	TkInternalAllocationType    AllocationType,
	TkSystemAllocationScope     AllocationScope);

typedef void (TK_CALL *PFN_tkInternalFreeNotification)(
	void*                       p_Allocator,
	tk_size_t                      Size,
	TkInternalAllocationType    AllocationType,
	TkSystemAllocationScope     AllocationScope);

typedef void (TK_CALL *PFN_tkInternalReallocationNotification)(
	void*                       p_Allocator,
	tk_size_t                      Size,
	TkInternalAllocationType    AllocationType,
	TkSystemAllocationScope     AllocationScope);

typedef struct TkAllocationCallbacks
{
	void*                                     p_Allocator;
	PFN_tkAllocationFunction                  pfn_Allocation;
	PFN_tkFreeFunction                        pfn_Free;
	PFN_tkReallocationFunction                pfn_Reallocation;
	PFN_tkIntenalAllocationNotification       pfn_AllocationNotification;
	PFN_tkInternalFreeNotification            pfn_FreeNotification;
	PFN_tkInternalReallocationNotification    pfn_ReallocationNotification;
} TkAllocationCallbacks;