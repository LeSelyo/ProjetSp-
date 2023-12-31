#include <err.h>
#include <float.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "square_detection.h"
#include "geometry.h"
#include "image.h"
#include "int_list.h"
#include "list.h"

intersection *find_line_intersections(
    int **edges, line edge1, int edge_num, int w, int h, int *intersection_num)
{

    int_list *intersections_x = li_create();
    int_list *intersections_y = li_create();
    int_list *edges_index = li_create();

    // iterate over the other edges
    for (int j = 0; j < edge_num; j++)
    {
        line edge2 = edge_to_line(edges[j]);

        // continue if the lines are equal
        if (lines_equal(edge1, edge2))
        {
            continue;
        }

        point intersection_pt = line_intersect(edge1, edge2);

        if (intersection_pt.x < 0 || intersection_pt.x >= w
            || intersection_pt.x >= w || intersection_pt.y < 0
            || intersection_pt.y >= h || intersection_pt.y >= h)
        {
            // if the points are not in the boundaries of the image, we
            // consider they do not intersect
            continue;
        }
        else
        {
            // lines intersect
            li_append(intersections_x, intersection_pt.x);
            li_append(intersections_y, intersection_pt.y);
            li_append(edges_index, j);
        }
    }

    // Convert the lists to an array
    int_list_node *edge_index_el = edges_index->head;
    int_list_node *inter_x_el = intersections_x->head;
    int_list_node *inter_y_el = intersections_y->head;

    *intersection_num = li_size(edges_index);
    intersection *intersections
        = malloc(sizeof(intersection) * (*intersection_num) + 1);

    if (intersections == NULL)
    {
        errx(1, "error when allocating memory in find_line_intersections");
    }

    for (int i = 0; i < (*intersection_num); i++)
    {
        point ppt;
        ppt.x = inter_x_el->value;
        ppt.y = inter_y_el->value;

        intersection inter;
        inter.line1 = edge1;
        inter.line2 = edge_to_line(edges[edge_index_el->value]);
        inter.pt = ppt;

        intersections[i] = inter;

        edge_index_el = edge_index_el->next;
        inter_x_el = inter_x_el->next;
        inter_y_el = inter_y_el->next;
    }

    li_free(intersections_x);
    li_free(intersections_y);
    li_free(edges_index);

    return intersections;
}

list *find_line_squares(int **edges, line edge_1, int edge_num, Image *image)
{
    list *squares = l_create();

    int intersection_num_1 = 0;

    point zero = {.x = 0, .y = 0};

    intersection *intersections_1 = find_line_intersections(edges, edge_1,
        edge_num, image->width, image->height, &intersection_num_1);

    for (int j = 0; j < intersection_num_1; j++)
    {
        int intersection_num_2 = 0;
        line edge_2 = intersections_1[j].line2;
        point c1 = intersections_1[j].pt;

        if (lines_equal(edge_2, edge_1))
            continue;

        if (points_equal(c1, zero))
            continue;

        intersection *intersections_2 = find_line_intersections(edges, edge_2,
            edge_num, image->width, image->height, &intersection_num_2);

        for (int k = 0; k < intersection_num_2; k++)
        {
            int intersection_num_3 = 0;
            line edge_3 = intersections_2[k].line2;
            point c2 = intersections_2[k].pt;

            if (lines_equal(edge_3, edge_1) || lines_equal(edge_3, edge_2))
                continue;

            if (points_equal(c2, zero) || points_equal(c1, c2))
                continue;

            intersection *intersections_3
                = find_line_intersections(edges, edge_3, edge_num,
                    image->width, image->height, &intersection_num_3);

            for (int l = 0; l < intersection_num_3; l++)
            {
                int intersection_num_4 = 0;
                line edge_4 = intersections_3[l].line2;
                point c3 = intersections_3[l].pt;

                if (lines_equal(edge_4, edge_1) || lines_equal(edge_4, edge_2)
                    || lines_equal(edge_4, edge_3))
                    continue;

                if (points_equal(c3, zero) || points_equal(c3, c1)
                    || points_equal(c3, c2))
                    continue;

                intersection *intersections_4
                    = find_line_intersections(edges, edge_4, edge_num,
                        image->width, image->height, &intersection_num_4);

                for (int m = 0; m < intersection_num_4; m++)
                {
                    line edge_5 = intersections_4[m].line2;
                    point c4 = intersections_4[m].pt;

                    if (points_equal(c4, zero) || points_equal(c4, c1)
                        || points_equal(c4, c2) || points_equal(c4, c3))
                        continue;

                    if (lines_equal(edge_5, edge_1))
                    {
                        square *sqr = malloc(sizeof(square));
                        sqr->c1 = c1;
                        sqr->c2 = c2;
                        sqr->c3 = c3;
                        sqr->c4 = c4;

                        l_append(squares, sqr);

                        // Temp solution: drawing the square
                        free(draw_line(image, image->width, image->height,
                            c1.x, c1.y, c2.x, c2.y, 0, 255, 0));
                        free(draw_line(image, image->width, image->height,
                            c2.x, c2.y, c3.x, c3.y, 0, 255, 0));
                        free(draw_line(image, image->width, image->height,
                            c3.x, c3.y, c4.x, c4.y, 0, 255, 0));
                        free(draw_line(image, image->width, image->height,
                            c4.x, c4.y, c1.x, c1.y, 0, 255, 0));
                        free(draw_line(image, image->width, image->height,
                            c1.x + 1, c1.y + 1, c2.x + 1, c2.y + 1, 0, 255,
                            0));
                        free(draw_line(image, image->width, image->height,
                            c2.x + 1, c2.y + 1, c3.x + 1, c3.y + 1, 0, 255,
                            0));
                        free(draw_line(image, image->width, image->height,
                            c3.x + 1, c3.y + 1, c4.x + 1, c4.y + 1, 0, 255,
                            0));
                        free(draw_line(image, image->width, image->height,
                            c4.x + 1, c4.y + 1, c1.x + 1, c1.y + 1, 0, 255,
                            0));
                        free(draw_line(image, image->width, image->height,
                            c1.x - 1, c1.y - 1, c2.x - 1, c2.y - 1, 0, 255,
                            0));
                        free(draw_line(image, image->width, image->height,
                            c2.x - 1, c2.y - 1, c3.x - 1, c3.y - 1, 0, 255,
                            0));
                        free(draw_line(image, image->width, image->height,
                            c3.x - 1, c3.y - 1, c4.x - 1, c4.y - 1, 0, 255,
                            0));
                        free(draw_line(image, image->width, image->height,
                            c4.x - 1, c4.y - 1, c1.x - 1, c1.y - 1, 0, 255,
                            0));
                    }
                }

                free(intersections_4);
            }

            free(intersections_3);
        }

        free(intersections_2);
    }

    free(intersections_1);

    return squares;
}

struct find_squares_thread_args
{
    int start;
    int n_edges;
    int edge_num;
    int **edges;
    Image *image;
    list *found_squares;
};

void *find_squares_thread(void *args)
{
    struct find_squares_thread_args *a = args;

    for (int j = 0; j < a->n_edges; j++)
    {
        list *found = find_line_squares(a->edges,
            edge_to_line(a->edges[a->start + j]), a->edge_num, a->image);

        l_merge(a->found_squares, found);

        // only free the container so the merged nodes are not lost
        free(found);
    }
}

list *find_squares(int **edges, int edge_num, Image *image)
{
    int i = 0;
    list *found_squares = l_create();

    // Number of threads available from the CPU
    int n_threads = sysconf(_SC_NPROCESSORS_ONLN);

    // Number of edges per thread
    int n_edges_per_thread = edge_num / n_threads;
    int r_edges_per_thread = edge_num % n_threads;

    // thread ids list
    pthread_t *threads = malloc(sizeof(pthread_t) * n_threads);
    struct find_squares_thread_args **args
        = malloc(sizeof(struct find_squares_thread_args *) * n_threads);

    fprintf(
        stderr,"\33[2K\r Treating Edges on %i threads", n_threads);

    for (int n = 0; n < n_threads; n++)
    {
        int n_edges = n_edges_per_thread;
        if (n == 0)
            n_edges += r_edges_per_thread;

        args[n] = malloc(sizeof(struct find_squares_thread_args));

        args[n]->start = i;
        args[n]->n_edges = n_edges;
        args[n]->edge_num = edge_num;
        args[n]->edges = edges;
        args[n]->image = image;
        args[n]->found_squares = found_squares;

        pthread_create(
            &threads[n], NULL, find_squares_thread, (void *)args[n]);

        i += n_edges;
    }

    for (int n = 0; n < n_threads; n++)
    {
        pthread_join(threads[n], NULL);
        free(args[n]);
    }
    free(args);
    free(threads);

    fprintf(stderr,"\33[2K\r Treated Edges: %i\n", edge_num);

    return found_squares;
}
