/**
* Copyright (C) Mellanox Technologies Ltd. 2001-2018.  ALL RIGHTS RESERVED.
*
* See file LICENSE for terms.
*/

#ifndef UCT_RC_MLX5_H
#define UCT_RC_MLX5_H

#include <uct/ib/rc/base/rc_iface.h>
#include <uct/ib/rc/base/rc_ep.h>
#include <uct/ib/mlx5/ib_mlx5.h>
#include <ucs/datastruct/queue.h>
#include <ucs/type/class.h>

#include "rc_mlx5.inl"

/**
 * RC remote endpoint
 */
typedef struct uct_rc_mlx5_ep {
    uct_rc_ep_t      super;
    unsigned         qp_num;

    struct {
        uct_ib_mlx5_txwq_t  wq;
    } tx;
} uct_rc_mlx5_ep_t;


UCS_CLASS_DECLARE(uct_rc_mlx5_ep_t, uct_iface_h);
UCS_CLASS_DECLARE_NEW_FUNC(uct_rc_mlx5_ep_t, uct_ep_t, uct_iface_h);
UCS_CLASS_DECLARE_DELETE_FUNC(uct_rc_mlx5_ep_t, uct_ep_t);

ucs_status_t uct_rc_mlx5_ep_put_short(uct_ep_h tl_ep, const void *buffer, unsigned length,
                                      uint64_t remote_addr, uct_rkey_t rkey);

ssize_t uct_rc_mlx5_ep_put_bcopy(uct_ep_h tl_ep, uct_pack_callback_t pack_cb,
                                 void *arg, uint64_t remote_addr, uct_rkey_t rkey);

ucs_status_t uct_rc_mlx5_ep_put_zcopy(uct_ep_h tl_ep, const uct_iov_t *iov, size_t iovcnt,
                                      uint64_t remote_addr, uct_rkey_t rkey,
                                      uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_get_bcopy(uct_ep_h tl_ep,
                                      uct_unpack_callback_t unpack_cb,
                                      void *arg, size_t length,
                                      uint64_t remote_addr, uct_rkey_t rkey,
                                      uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_get_zcopy(uct_ep_h tl_ep, const uct_iov_t *iov, size_t iovcnt,
                                      uint64_t remote_addr, uct_rkey_t rkey,
                                      uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_am_short(uct_ep_h tl_ep, uint8_t id, uint64_t header,
                                     const void *payload, unsigned length);

ssize_t uct_rc_mlx5_ep_am_bcopy(uct_ep_h tl_ep, uint8_t id,
                                uct_pack_callback_t pack_cb, void *arg,
                                unsigned flags);

ucs_status_t uct_rc_mlx5_ep_am_zcopy(uct_ep_h tl_ep, uint8_t id, const void *header,
                                     unsigned header_length, const uct_iov_t *iov,
                                     size_t iovcnt, unsigned flags,
                                     uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_atomic_cswap64(uct_ep_h tl_ep, uint64_t compare, uint64_t swap,
                                           uint64_t remote_addr, uct_rkey_t rkey,
                                           uint64_t *result, uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_atomic_cswap32(uct_ep_h tl_ep, uint32_t compare, uint32_t swap,
                                           uint64_t remote_addr, uct_rkey_t rkey,
                                           uint32_t *result, uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_atomic64_post(uct_ep_h ep, unsigned opcode, uint64_t value,
                                          uint64_t remote_addr, uct_rkey_t rkey);

ucs_status_t uct_rc_mlx5_ep_atomic32_post(uct_ep_h ep, unsigned opcode, uint32_t value,
                                          uint64_t remote_addr, uct_rkey_t rkey);

ucs_status_t uct_rc_mlx5_ep_atomic64_fetch(uct_ep_h ep, uct_atomic_op_t opcode,
                                           uint64_t value, uint64_t *result,
                                           uint64_t remote_addr, uct_rkey_t rkey,
                                           uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_atomic32_fetch(uct_ep_h ep, uct_atomic_op_t opcode,
                                           uint32_t value, uint32_t *result,
                                           uint64_t remote_addr, uct_rkey_t rkey,
                                           uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_flush(uct_ep_h tl_ep, unsigned flags, uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_fc_ctrl(uct_ep_t *tl_ep, unsigned op,
                                    uct_rc_fc_request_t *req);

unsigned uct_rc_mlx5_iface_progress(void *arg);

#if IBV_EXP_HW_TM
ucs_status_t uct_rc_mlx5_ep_tag_eager_short(uct_ep_h tl_ep, uct_tag_t tag,
                                            const void *data, size_t length);

ssize_t uct_rc_mlx5_ep_tag_eager_bcopy(uct_ep_h tl_ep, uct_tag_t tag,
                                       uint64_t imm,
                                       uct_pack_callback_t pack_cb,
                                       void *arg, unsigned flags);

ucs_status_t uct_rc_mlx5_ep_tag_eager_zcopy(uct_ep_h tl_ep, uct_tag_t tag,
                                            uint64_t imm, const uct_iov_t *iov,
                                            size_t iovcnt, unsigned flags,
                                            uct_completion_t *comp);

ucs_status_ptr_t uct_rc_mlx5_ep_tag_rndv_zcopy(uct_ep_h tl_ep, uct_tag_t tag,
                                               const void *header,
                                               unsigned header_length,
                                               const uct_iov_t *iov,
                                               size_t iovcnt, unsigned flags,
                                               uct_completion_t *comp);

ucs_status_t uct_rc_mlx5_ep_tag_rndv_request(uct_ep_h tl_ep, uct_tag_t tag,
                                             const void* header,
                                             unsigned header_length,
                                             unsigned flags);
#endif

#endif
