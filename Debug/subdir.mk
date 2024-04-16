################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADAS.c \
../ADC_Prog.c \
../Buzzer_Prog.c \
../DIO_Prog.c \
../EXTINT_Prog.c \
../GIE_Prog.c \
../Keypad_prog.c \
../LCD_prog.c \
../LED_Prog.c \
../POT_Prog.c \
../Timer1_Prog.c \
../main.c 

OBJS += \
./ADAS.o \
./ADC_Prog.o \
./Buzzer_Prog.o \
./DIO_Prog.o \
./EXTINT_Prog.o \
./GIE_Prog.o \
./Keypad_prog.o \
./LCD_prog.o \
./LED_Prog.o \
./POT_Prog.o \
./Timer1_Prog.o \
./main.o 

C_DEPS += \
./ADAS.d \
./ADC_Prog.d \
./Buzzer_Prog.d \
./DIO_Prog.d \
./EXTINT_Prog.d \
./GIE_Prog.d \
./Keypad_prog.d \
./LCD_prog.d \
./LED_Prog.d \
./POT_Prog.d \
./Timer1_Prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


