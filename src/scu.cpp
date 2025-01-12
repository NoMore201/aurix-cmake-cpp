#include "scu.hpp"

#include <IfxScu_reg.h>
#include <IfxScu_bf.h>

namespace
{

} // anonymous namespace

void Hal::Scu::clear_cpu_endinit(Password password)
{
    auto& watchdog = MODULE_SCU.WDTCPU[0];

    if (watchdog.CON0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        watchdog.CON0.U = (1U << IFX_SCU_WDTCPU_CON0_ENDINIT_OFF) | (0U << IFX_SCU_WDTCPU_CON0_LCK_OFF)
                          | (password << IFX_SCU_WDTCPU_CON0_PW_OFF) | (watchdog.CON0.B.REL << IFX_SCU_WDTCPU_CON0_REL_OFF);
    }

    /* Clear ENDINT and set LCK bit in Config_0 register */
    watchdog.CON0.U = (0U << IFX_SCU_WDTCPU_CON0_ENDINIT_OFF) | (1U << IFX_SCU_WDTCPU_CON0_LCK_OFF)
                      | (password << IFX_SCU_WDTCPU_CON0_PW_OFF) | (watchdog.CON0.B.REL << IFX_SCU_WDTCPU_CON0_REL_OFF);

    /* read back ENDINIT and wait until it has been cleared */
    while (watchdog.CON0.B.ENDINIT == 1)
    {
    }
}

void Hal::Scu::set_cpu_endinit(Password password)
{
    auto& watchdog = MODULE_SCU.WDTCPU[0];

    if (watchdog.CON0.B.LCK)
    {
        /* see Table 1 (Pass.word Access Bit Pattern Requirements) */
        watchdog.CON0.U = (1U << IFX_SCU_WDTCPU_CON0_ENDINIT_OFF) | (0U << IFX_SCU_WDTCPU_CON0_LCK_OFF)
                          | (password << IFX_SCU_WDTCPU_CON0_PW_OFF) | (watchdog.CON0.B.REL << IFX_SCU_WDTCPU_CON0_REL_OFF);
    }

    /* Set ENDINT and set LCK bit in Config_0 register */
    watchdog.CON0.U = (1U << IFX_SCU_WDTCPU_CON0_ENDINIT_OFF) | (1U << IFX_SCU_WDTCPU_CON0_LCK_OFF)
                      | (password << IFX_SCU_WDTCPU_CON0_PW_OFF) | (watchdog.CON0.B.REL << IFX_SCU_WDTCPU_CON0_REL_OFF);

    /* read back ENDINIT and wait until it has been set */
    while (watchdog.CON0.B.ENDINIT == 0)
    {
    }
}

Hal::Scu::Password Hal::Scu::get_cpu_password()
{
    Password password{};
    auto&    watchdog = MODULE_SCU.WDTCPU[0];

    password = watchdog.CON0.B.PW;
    password ^= 0x003F;

    return password;
}

void Hal::Scu::disable_cpu_watchdog(Password password)
{
    auto& watchdog = MODULE_SCU.WDTCPU[0];

    CpuEndinitGuard guard{password};

    watchdog.CON1.B.DR = 1;
}