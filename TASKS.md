Tasks:

- Remove destructor of **VAO** 'cause after `Mesh::Mesh` its destructs. This causes **GL_INVALID_OPERATION** in `draw` function. (`vao.bind()`).
