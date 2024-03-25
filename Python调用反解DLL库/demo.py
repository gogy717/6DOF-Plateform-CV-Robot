angle_list = [60, 117, 62, 122, 67, 115]

# converted_list = [str(angle) for angle in angle_list]
# angle_str = ','.join(converted_list)
# angle_str+="\r"
# angle_str= "A"+angle_str

def convert_angle_to_string(angles):
    return 'A'+','.join(str(angle) for angle in angles)+'\r'
angle_str = convert_angle_to_string(angle_list)


print(angle_str)
