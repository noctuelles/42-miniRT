# 42-miniRT

In space, any orientation can be describe using two angles, just like in the plan, it can be describe with one angle.
The technique used here to rotate primitives is to compute $\alpha$ and $\beta$ angle, commonly called the pitch and yaw angle.


$$
\alpha = \frac
{
\arctan2(\sqrt{{x_{\vec{u}}}^{2} + {z_{\vec{u}}}^{2}}}
{
{y_{\vec{u}}}^{2}
}
$$
