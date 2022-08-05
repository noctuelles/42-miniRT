# 42-miniRT

## The orientation vector

The subject gives room for interpretation : what should this "orientation vector" do ?
It could be interpreted as this : imagine a cylinder with a vector on his top, this vector is pointing where the cylinder should be oriented.

Given $\vec{d}(0., 1., 0.)$, the cylinder should be aligned with the $y axis$.

In space, any orientation can be describe using two angles, just like in the plan, it can be describe with one angle.

The technique used here to rotate primitives is to compute $\alpha$ and $\beta$ angle, commonly called the pitch and yaw angle.
Given $\vec{u}$, the angle between the up axis and the vector can be compute with : 

$$
\alpha = \frac
{
\arctan2(\sqrt{{x_{\vec{u}}}^{2} + {z_{\vec{u}}}^{2}}}
{
{y_{\vec{u}}}^{2}
}
$$
