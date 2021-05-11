#include "draw.h"
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "camera.h"

void draw_triangles(const struct Model* model)
{
	int i, k;
	int vertex_index, normal_index;
	double x, y, z, normal_x, normal_y, normal_z;

	glBegin(GL_TRIANGLES);

	for (i = 0; i < model->n_triangles; ++i) {
		for (k = 0; k < 3; ++k) {
			normal_index = model->triangles[i].points[k].normal_index;
			normal_x = model->normals[normal_index].x;
			normal_y = model->normals[normal_index].y;
			normal_z = model->normals[normal_index].z;
			glNormal3d(normal_x, normal_y, normal_z);
			vertex_index = model->triangles[i].points[k].vertex_index;
			x = model->vertices[vertex_index].x;
			y = model->vertices[vertex_index].y;
			z = model->vertices[vertex_index].z;
            switch(k){
            case 0:
                glTexCoord2f(0, 0);
                break;
            case 1:
                glTexCoord2f(0.1*z, 0);
                break;
            case 2:
                glTexCoord2f(0, 0.01);
                break;
            }
			glVertex3d(x, y, z);

		}
	}

	glEnd();
}


void draw_quads(const struct Model* model)
{
    int i, k;
    int vertex_index, texture_index;
    double x, y, z, u, v;

	glBegin(GL_QUADS);

    for (i = 0; i < model->n_quads; ++i) {
        for (k = 0; k < 4; ++k) {

            texture_index = model->quads[i].points[k].texture_index;
            u = model->texture_vertices[texture_index].u;
            v = model->texture_vertices[texture_index].v;
            glTexCoord2f(u, 1-v);

            vertex_index = model->quads[i].points[k].vertex_index;
            x = model->vertices[vertex_index].x;
            y = model->vertices[vertex_index].y;
            z = model->vertices[vertex_index].z;
            glVertex3d(x, y, z);
        }
    }

    glEnd();
}



void draw_normals(const struct Model* model, double skybox_size2)
{
	int i;
	double x1, y1, z1, x2, y2, z2;

	glColor3f(0, 0, 1);

	glBegin(GL_LINES);

	for (i = 0; i < model->n_vertices; ++i) {
		x1 = model->vertices[i].x;
		y1 = model->vertices[i].y;
		z1 = model->vertices[i].z;
		x2 = x1 + model->normals[i].x * skybox_size2;
		y2 = y1 + model->normals[i].y * skybox_size2;
		z2 = z1 + model->normals[i].z * skybox_size2;
		glVertex3d(x1, y1, z1);
		glVertex3d(x2, y2, z2);
	}
	glEnd();
}



void draw_model(const struct Model* model)
{
	draw_triangles(model);
	draw_quads(model);
}





void draw_skybox(Entity skybox)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    // Center the Skybox around the given x,y,z position
    float position = -(float)skybox_size / 2;


    // Draw Front side
    glBindTexture(GL_TEXTURE_2D, skybox.texture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position, position, position + skybox_size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position, position + skybox_size, position + skybox_size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position + skybox_size, position + skybox_size, position + skybox_size);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position + skybox_size, position, position + skybox_size);
    glEnd();

    // Draw Back side
    glBindTexture(GL_TEXTURE_2D, skybox.texture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position + skybox_size, position, position);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position + skybox_size, position + skybox_size, position);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position, position + skybox_size, position);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position, position, position);
    glEnd();

    // Draw Left side
    glBindTexture(GL_TEXTURE_2D, skybox.texture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position, position + skybox_size, position);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position, position + skybox_size, position + skybox_size);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position, position, position + skybox_size);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position, position, position);
    glEnd();

    // Draw Right side
    glBindTexture(GL_TEXTURE_2D, skybox.texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position + skybox_size, position, position);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position + skybox_size, position, position + skybox_size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position + skybox_size, position + skybox_size, position + skybox_size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position + skybox_size, position + skybox_size, position);
    glEnd();

    // Draw Up side
    glBindTexture(GL_TEXTURE_2D, skybox.texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position + skybox_size, position + skybox_size, position);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position + skybox_size, position + skybox_size, position + skybox_size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position, position + skybox_size, position + skybox_size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position, position + skybox_size, position);
    glEnd();

    // Draw Down side
    glBindTexture(GL_TEXTURE_2D, skybox.texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(position, position, position);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(position, position, position + skybox_size);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(position + skybox_size, position, position + skybox_size);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(position + skybox_size, position, position);
    glEnd();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}



void draw_environment(World world, Rotate* rotate, Move move ){
	glEnable(GL_TEXTURE_2D);




	//Draw the skybox.
	draw_skybox(world.skybox);


	//Draw the ds.
	glPushMatrix();

		glTranslatef(0,0,0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, world.ds.material_ambient);
		glBindTexture(GL_TEXTURE_2D, world.ds.texture);
		glScalef(1.0f, 1.0f, 1.0f);
		//glRotatef(rotate->ds_rotation, 1, 1, 1);
		draw_model(&world.ds.model);

    glPopMatrix();


    //Draw the isd.
    glPushMatrix();

    		glTranslatef (move.isd.x,move.isd.y,move.isd.z);
    		glMaterialfv(GL_FRONT, GL_AMBIENT, world.isd.material_ambient);
    		glBindTexture(GL_TEXTURE_2D, world.isd.texture);
    		glScalef(1.0f, 1.0f, 1.0f);
    		glRotatef(rotate->isd_rotation, 0, 0, 1);
    		draw_model(&world.isd.model);

   glPopMatrix();





}

