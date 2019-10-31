//#ifdef STSTM32
#include "endstop.h"

Endstop *endstop_init(Stepper *_stepper, uint8_t *_name, uint32_t _port, uint8_t _ext, uint16_t _pin)
{
    endstop = (Endstop *)malloc(sizeof(Endstop));

    enum types type = ENDSTOP;
	endstop->device.type = type;
    strcpy(endstop->device.name, _name);

    endstop->parent_stepper = _stepper;

    endstop->port = _port;
    endstop->pin = _pin;
    endstop->ext = _ext;

    endstop_setup_gpio();

    //there are 3 groups of EXT interrupts
    // EXTI0_IRQn - EXTI4_IRQn  -> 0-4
    // EXTI9_5_IRQn -> 5-9
    // EXTI15_10_IRQn -> 10-15

    return endstop;
}


void endstop_deinit()
{
    free(endstop);
}

void endstop_setup_gpio()
{
    GPIO_InitTypeDef gpio;

	gpio.Pin = endstop->pin;
	gpio.Mode = GPIO_MODE_IT_RISING;
	gpio.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(endstop->port, &gpio);

    HAL_NVIC_EnableIRQ(endstop->ext);
}

uint8_t endstop_clicked()
{
    /*
    if(HAL_GPIO_ReadPin(e->port, e->pin))
        return 1;
    else
        return 0;
    */
    endstop->clicked = HAL_GPIO_ReadPin(endstop->port, endstop->pin);
    return endstop->clicked;
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(endstop->pin);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == endstop->pin)
    {
        if(HAL_GPIO_ReadPin(endstop->port, endstop->pin))
        {
            HAL_TIM_PWM_Stop(&endstop->parent_stepper->timer, endstop->parent_stepper->channel);
            endstop->clicked = 1;
        }
            
        else
        {
            endstop->clicked = 0;
        }    
    }
}

//#endif // STSTM32