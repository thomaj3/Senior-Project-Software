/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
unsigned char eight_bit_unsigned_round(double x)
{
    unsigned char x_round;
    x_round = (unsigned char) (x + 0.5); //casting double + .5 to uint8_t (flooring) to round
    return x_round;
}

/* [] END OF FILE */
