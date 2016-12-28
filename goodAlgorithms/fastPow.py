def fast_power(a, n, m): # (a ^ n) % m
    """
    This function assumes that n >= 0
    """
    result = 1
    value = a
    power = n
    while power > 0:
        if power % 2 == 1:
            result = result * value
            result %= m
        value = value * value
        value %= m
        power = power//2
    return result