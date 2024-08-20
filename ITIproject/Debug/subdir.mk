################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../CLCD_program.c \
../DIO_program.c \
../EXTI_program.c \
../GIE_program.c \
../MAP.c \
../TIMER1_PROGRAM.c \
../TIMER_program.c \
../USART_program.c \
../main.c \
../servo.c 

OBJS += \
./ADC_program.o \
./CLCD_program.o \
./DIO_program.o \
./EXTI_program.o \
./GIE_program.o \
./MAP.o \
./TIMER1_PROGRAM.o \
./TIMER_program.o \
./USART_program.o \
./main.o \
./servo.o 

C_DEPS += \
./ADC_program.d \
./CLCD_program.d \
./DIO_program.d \
./EXTI_program.d \
./GIE_program.d \
./MAP.d \
./TIMER1_PROGRAM.d \
./TIMER_program.d \
./USART_program.d \
./main.d \
./servo.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


