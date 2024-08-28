.section .text
.global _get_hart_id

_get_hart_id:
        csrr a0, mhartid
        ret

# return 0 if success, 1 if failure
# a0 should be an address 
.global _try_lock 
_try_lock:
  mv t1, a0
  li a0, 1
  amoswap.w.aq a0, a0, (t1)
  ret

# release lock regardless of if we are holding it
# returns the previous value of the lock
.global _release_lock
_release_lock:
  mv t1, a0
  li a0, 0
  amoswap.w.aq a0, a0, (t1)
  ret

.global _enable_interrupts
_enable_interrupts:
  ret

.global _disable_interrupts
_disable_interrupts:
  ret

.global _get_interrupt_cause
_get_interrupt_cause:
  csrr a0, ucause
  ret

