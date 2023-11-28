import cv2
import numpy as np

for name in ["bk", "dn", "ft", "lf", "rt", "up"]:
    img = cv2.imread('skybox/ar_{name}.png'.format(name = name))

    resized = cv2.resize(img, (1024, 1024), interpolation= cv2.INTER_AREA)

    cv2.imwrite('skybox/arc_{name}.png'.format(name = name), resized)

