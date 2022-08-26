
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define USER "Admin"
#define PASS "admin123"

#define VALOR_CENTINELA "-1"

#define CLEAR "cls"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

// **********************************************DECLARACIÓN DE FUNCIONES***********************************

void tituloAdmin();
void tituloEncargado();
void tituloLogin();
int menuAdmin();
int menuUsuario();
int menuInventario();
int menuSucursal();

struct registroUsuario login();

struct registroUsuario capturar();               
struct registroUsuario eliminarU();              
struct registroUsuario eliminarFisica();         
struct registroUsuario modificarU();             
struct registroUsuario consultarU();             
struct registroUsuario consultarTodosUsuarios(); 

struct registroSucursal capturarS();                
struct registroSucursal eliminarS();                
struct registroSucursal eliminarFisicaS();          
struct registroSucursal modificarS();               
struct registroSucursal consultarS();               
struct registroSucursal consultarTodasSucursales(); 

struct registroProductos capturarP1(); 
struct registroProductos capturarP2();
struct registroProductos capturarP3();
struct registroProductos eliminarP();                   
struct registroProductos eliminarFisicaP();             
struct registroProductos consultarTodosProductos();     
struct registroProductos consultarProductosCategoria(); 
void productSuc();
struct registroProductos consultarProductoSucursales1();
struct registroProductos consultarProductoSucursales2();
struct registroProductos consultarProductoSucursales3();
struct registroProductos consultaEnSucursal();
struct registroProductos modificarP(); 

struct registroVentas capturarV();       
struct registroVentas consultarVentas(); 

struct registroUsuario
{
    char id[50];
    char usuario[50];
    char password[15];
    char sucursal[50];
};

struct registroSucursal
{
    char id[50];
    char nombre[30];
    char direccion[50];
    char encargado[25];
};

struct registroProductos
{
    char idProducto[50];
    char nombreProducto[50];
    char marcaProducto[50];
    int categoriaProducto;
    float precioCompra;
    float precioVenta;
    int existencia;
};

struct registroVentas
{
    int id;
    char producto[50];
    int cantidad;
    float ventaTotal;
};

int menuConsultaInventario();
int menuConsultaInventario()
{

    int opcArchivo;

    printf("\n\n");
    printf("\t\t\t\t\t\t\tMENU DE INVENTARIOS\n");
    printf("\t\t\t\t\t\t\t====================\n\n");
    printf(" \t\t\t\t\t\t[1]. Inventario1\n");
    printf(" \t\t\t\t\t\t[2]. Inventario2\n");
    printf(" \t\t\t\t\t\t[3]. Inventario3\n");

    printf(" \n\n");

    printf("\t\t\t\t\t\tEelige una opcion de Inventario: ");
    scanf("%d%*c", &opcArchivo);

    return opcArchivo;
}

// **********************************************FN1 REGISTRO DE USUARIOS************************************

struct registroUsuario capturar()
{

    struct registroUsuario registroUser;

    FILE *ptrArchivo = NULL;

    char ID[50], nombreUsuario[50], respuesta, sucursal[50] = " ";
    int existeID, existeUser;

    do
    {
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t    >> REGISTRAR USUARIOS <<\n");
        printf("\t\t\t\t\t\t       ==================\n\n");

        do
        {
            existeID = 0;

            printf("\n\t\t\t\t\t       Introduce ID de usuario: ");
            scanf(" %[^\n]%*c", ID);

            ptrArchivo = fopen("Usuarios.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registroUser, sizeof(registroUser), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registroUser.id, ID) == 0)
                    {
                        existeID = 1;
                        break;
                    }
                    fread(&registroUser, sizeof(registroUser), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (existeID == 1)
            {
                printf("\n\t\t\t\t\tEl  ID %s ya ha sido registrado previamente\n", ID);
                printf("\t\t\t\t\tNo puede registrar dos usuarios con el mismo ID.\n\n\n");
            }

        } while (existeID == 1);

        do
        {
            existeUser = 0;

            printf("\t\t\t\t\t       Introduce nombre de usuario: ");
            scanf("%[^\n]%*c", nombreUsuario);

            ptrArchivo = fopen("Usuarios.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registroUser, sizeof(registroUser), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registroUser.usuario, nombreUsuario) == 0)
                    {
                        existeUser = 1;
                        break;
                    }
                    fread(&registroUser, sizeof(registroUser), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (existeUser == 1)
            {
                printf("\n\t\t\t\t\tEl  usuario %s ya ha sido registrado previamente\n", nombreUsuario);
                printf("\t\t\t\t\tNo puede registrar dos usuarios con el mismo nombre.\n\n\n");
            }

        } while (existeUser == 1);

        if (existeUser == 0)
        {
            strcpy(registroUser.id, ID);
            strcpy(registroUser.usuario, nombreUsuario);
            printf("\t\t\t\t\t       Introduce un password: ");
            scanf("%s%*c", registroUser.password);
            strcpy(registroUser.sucursal, sucursal);
        }

        if (ptrArchivo != NULL || ptrArchivo == NULL)
        {
            ptrArchivo = fopen("Usuarios.dat", "ab");
            if (ptrArchivo != NULL)
            {
                fwrite(&registroUser, sizeof(registroUser), 1, ptrArchivo);
                printf("\n\n\t\t\t\t\t        Usuario creado correctamente\n\n");
            }
            fclose(ptrArchivo);
        }
        else
        {
            printf("\n\n\t\t\t\t\t Usuario no creado");
        }

        printf("\n\t\t\t\t\t Desea seguir registrando usuarios? [S/N]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while (respuesta == 'S' || respuesta == 's');
};

// **********************************************FN10 ELIMINAR UN USUARIO************************************

struct registroUsuario eliminarU()
{

    struct registroUsuario eUsuario;

    FILE *ptrArchivo = NULL;

    int encontrar, elimina;
    char repite = 1, respuesta, respuesta1, idUser[50];

    do
    {
        elimina = 0;
        encontrar = 0;
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t>> ELIMINAR USUARIO POR CODIGO <<\n");
        printf("\t\t\t\t\t\t   ===========================\n\n");

        ptrArchivo = fopen("Usuarios.dat", "r+b");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese la clave del usuario: ");
            scanf(" %[^\n]%*c", idUser);
            printf("\n");

            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&eUsuario, sizeof(eUsuario), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {

                if (strcmp(eUsuario.id, idUser) == 0)
                {
                    encontrar = 1;

                    printf("\t\t  %10s", eUsuario.id);
                    printf("%25s", eUsuario.usuario);
                    printf("%25s", eUsuario.password);
                    printf("%25s", eUsuario.sucursal);
                    printf("\n");

                    printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                    printf("\n\t\t\t\t\tEsta seguro de querer eliminar este usuario? [S/N]: ");
                    scanf("%s%*c", &respuesta);

                    if (respuesta == 'S' || respuesta == 's')
                    {

                        long pos = ftell(ptrArchivo) - sizeof(eUsuario);
                        fseek(ptrArchivo, pos, SEEK_SET);
                        strcpy(eUsuario.id, VALOR_CENTINELA);
                        fwrite(&eUsuario, sizeof(eUsuario), 1, ptrArchivo);
                        printf("\n\t\t\t\t\t          Usuario eliminado correctamente\n\n");

                        elimina = 1;

                        break;
                    }
                }

                fread(&eUsuario, sizeof(eUsuario), 1, ptrArchivo);
            }
        }

        fclose(ptrArchivo);

        if (ptrArchivo == NULL)
        {
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            printf("\t\t   No existe ningun usuario registrado\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            printf("\n\t\t\t\t\t     Desea intentarlo de nuevo? [S/N]: ");
            scanf("%s%*c", &respuesta);
        }

        if (ptrArchivo != NULL)
        {

            if (idUser != eUsuario.id && encontrar == 0 && elimina == 0)
            {
                printf("\t\t   No existe ningun usuario con esta clave\n");
                printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                printf("\n\t\t\t\t\t Desea ingresar una clave valida de ususario? [S/N]: ");
                scanf("%s%*c", &respuesta);
            }
            if (elimina == 1)
            {
                printf("\n\t\t\t\t\t        Desea eliminar otro usuario? [S/N]: ");
                scanf("%s%*c", &respuesta1);
            }
        }
        printf("\n");

    } while ((respuesta == 'S' || respuesta == 's'));

    if (ptrArchivo != NULL)
    {
        eliminarFisica();
    }
}

struct registroUsuario eliminarFisica()
{

    struct registroUsuario eFisica;

    FILE *ptrArchivo = NULL;
    FILE *temporal = NULL;

    char elimina = 0;

    ptrArchivo = fopen("Usuarios.dat", "rb");
    temporal = fopen("Temporal.dat", "wb");

    if (ptrArchivo != NULL || temporal != NULL)
    {
        fread(&eFisica, sizeof(eFisica), 1, ptrArchivo);
        while (!feof(ptrArchivo))
        {
            if (strcmp(eFisica.id, VALOR_CENTINELA) != 0)
            {
                fwrite(&eFisica, sizeof(eFisica), 1, temporal);
            }
            fread(&eFisica, sizeof(eFisica), 1, ptrArchivo);
        }
        fclose(ptrArchivo);
        fclose(temporal);

        remove("Usuarios.dat");
        rename("Temporal.dat", "Usuarios.dat");

        elimina = 1;
    }
}

// _____________________________________________FN5 MODIFICAR REGISTRO DE USUARIO_________________________________

struct registroUsuario modificarU()
{

    struct registroUsuario mUsuario;

    FILE *ptrArchivo = NULL;

    int modificado = 0;
    int existe = 0;
    int encontrar, opcion, existeUser;
    char respuesta, codigo[50], nombreUsuario[50];
    do
    {
        encontrar = 0;
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t>> MODIFICAR USUARIOS POR CODIGO <<\n");
        printf("\t\t\t\t\t\t   =============================\n\n");

        ptrArchivo = fopen("Usuarios.dat", "r+b");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese la clave del usuario: ");
            scanf("%*c%[^\n]%*c", codigo);
            printf("\n");

            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&mUsuario, sizeof(mUsuario), 1, ptrArchivo);
            while (!feof(ptrArchivo) && encontrar == 0)
            {

                if (strcmp(codigo, mUsuario.id) == 0)
                {
                    printf("\t\t  %10s", mUsuario.id);
                    printf("%25s", mUsuario.usuario);
                    printf("%25s", mUsuario.password);
                    printf("%25s", mUsuario.sucursal);
                    printf("\n");

                    printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                    do
                    {
                        printf("\n\t\t\t\t\t\t     [1]. Todos los registros\n");
                        printf("\t\t\t\t\t\t     [2]. Usuario\n");
                        printf("\t\t\t\t\t\t     [3]. Password\n");
                        printf("\t\t\t\t\t\t     [0]. Volver\n");
                        printf("\n");
                        printf("\t\t\t\t\t   Introduce la opcion que deseas ejecutar: [ ]\b\b");
                        scanf("%d%*c\0", &opcion);

                        switch (opcion)
                        {

                        case 1:

                            printf("\n\t\t\t\t\t   Modificar todos los registros del usuario\n\n");

                            printf("\t\t\t\t\t        ID: %s\n", mUsuario.id);

                            printf("\t\t\t\t\t        USUARIO: ");
                            scanf("%[^\n]%*c", mUsuario.usuario);

                            printf("\t\t\t\t\t        PASSWORD: ");
                            scanf("%s%*c", mUsuario.password);

                            long pos = ftell(ptrArchivo) - sizeof(mUsuario);
                            fseek(ptrArchivo, pos, SEEK_SET);
                            fwrite(&mUsuario, sizeof(mUsuario), 1, ptrArchivo);
                            system(CLEAR);
                            tituloAdmin();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 2:

                            printf("\n\t\t\t\t\t        Modificar nombre de usuario\n\n");

                            printf("\t\t\t\t\t        ID: %s\n", mUsuario.id);

                            printf("\t\t\t\t\t        USUARIO: ");
                            scanf("%[^\n]%*c", mUsuario.usuario);

                            long pos1 = ftell(ptrArchivo) - sizeof(mUsuario);
                            fseek(ptrArchivo, pos1, SEEK_SET);
                            fwrite(&mUsuario, sizeof(mUsuario), 1, ptrArchivo);
                            system(CLEAR);
                            tituloAdmin();
                            printf("\n\t\t\t\t\t          Datos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 3:

                            printf("\n\t\t\t\t\t        Modificar password de usuario\n\n");

                            printf("\t\t\t\t\t        ID: %s\n", mUsuario.id);

                            printf("\t\t\t\t\t        PASSWORD: ");
                            scanf("%s%*c", mUsuario.password);

                            long pos2 = ftell(ptrArchivo) - sizeof(mUsuario);
                            fseek(ptrArchivo, pos2, SEEK_SET);
                            fwrite(&mUsuario, sizeof(mUsuario), 1, ptrArchivo);
                            system(CLEAR);
                            tituloAdmin();
                            printf("\n\t\t\t\t\t          Datos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 0:
                            menuUsuario();

                        default:
                            printf("\n\t\t\t\t\t        La opcion no existe, intentelo de nuevo\n\n");
                            modificado = 0;
                        }

                        if (modificado == 1)
                        {
                            printf("\n\t\t\t\t\t           ==> USUARIO MODIFICADO <==\n");
                            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
                            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
                            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                            printf("\t\t  %10s", mUsuario.id);
                            printf("%25s", mUsuario.usuario);
                            printf("%25s", mUsuario.password);
                            printf("%25s", mUsuario.sucursal);
                            printf("\n");

                            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
                        }
                    } while (modificado == 0);
                }

                fread(&mUsuario, sizeof(mUsuario), 1, ptrArchivo);
            }
        }

        fclose(ptrArchivo);

        if (ptrArchivo == NULL)
        {
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            printf("\t\t   No existe ningun usuario registrado\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            printf("\n\t\t\t\t\t     Desea intentarlo de nuevo? [S/N]: ");
            scanf("%s%*c", &respuesta);
        }

        if (ptrArchivo != NULL)
        {

            if (codigo != mUsuario.id && modificado == 0)
            {
                printf("\t\t   No existe ningun usuario con esta clave\n");
                printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
                printf("\n\t\t\t\t\t     Desea intentarlo de nuevo? [S/N]: ");
                scanf("%s%*c", &respuesta);
            }

            if (modificado == 1)
            {
                printf("\n\t\t\t\t\t      Desea modificar otro usuario? [S/N]: ");
                scanf("%s%*c", &respuesta);

                printf("\n");
            }
        }
    } while (respuesta == 'S' || respuesta == 's');
};

// _____________________________________________FN12 CONSULTA DE UN SOLO USUARIO_________________________________

struct registroUsuario consultarU()
{

    struct registroUsuario cUsuario;

    FILE *ptrArchivo = NULL;

    char codigo[50], respuesta;
    int encontrar;

    do
    {

        encontrar = 0;
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t>> CONSULTAR USUARIOS POR CODIGO <<\n");
        printf("\t\t\t\t\t\t   =============================\n\n");

        ptrArchivo = fopen("Usuarios.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese la clave del usuario: ");
            scanf(" %[^\n]%*c", codigo);
            printf("\n");

            printf("\n\t\t\t\t                     ==> USUARIO REGISTRADO <==\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&cUsuario, sizeof(cUsuario), 1, ptrArchivo);
            while (!feof(ptrArchivo) && encontrar == 0)
            {
                if (strcmp(codigo, cUsuario.id) == 0)
                {
                    printf("\t\t  %10s", cUsuario.id);
                    printf("%25s", cUsuario.usuario);
                    printf("%25s", cUsuario.password);
                    printf("%25s", cUsuario.sucursal);
                    printf("\n");

                    encontrar = 1;
                }
                fread(&cUsuario, sizeof(cUsuario), 1, ptrArchivo);
            }

            if (encontrar == 0)
            {
                printf("\t\t   No existe ningun usuario con esta clave\n");
            }

            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }

        fclose(ptrArchivo);

        if (ptrArchivo == NULL)
        {
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            printf("\t\t   No existe ningun usuario registrado\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            printf("\n\t\t\t\t\t     Desea intentarlo de nuevo? [S/N]: ");
            scanf("%s%*c", &respuesta);
        }

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t        Desea consultar otro usuario? [S/N]: ");
            scanf("%s%*c", &respuesta);
        }
        printf("\n");

    } while (respuesta == 'S' || respuesta == 's');
};

// ____________________________________FN7 CONSULTA DE TODOS LOS USUARIOS__________________________________

struct registroUsuario consultarTodosUsuarios()
{

    struct registroUsuario consultaUsuarios;

    FILE *ptrArchivo = NULL;

    int cont = 0;
    char respuesta;

    do
    {
        system(CLEAR);
        tituloAdmin();

        ptrArchivo = fopen("Usuarios.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t                    ==> USUARIOS REGISTRADOS <==\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&consultaUsuarios, sizeof(consultaUsuarios), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {

                printf("\t\t  %10s", consultaUsuarios.id);
                printf("%25s", consultaUsuarios.usuario);
                printf("%25s", consultaUsuarios.password);
                printf("%25s", consultaUsuarios.sucursal);
                printf("\n");

                cont++;

                fread(&consultaUsuarios, sizeof(consultaUsuarios), 1, ptrArchivo);
            }
            if (cont == 0)
            {
                printf("\t\t   No existen usuarios registrados\n");
            }

            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }

        fclose(ptrArchivo);

        if (ptrArchivo == NULL)
        {
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            printf("\t\t   No existe ningun usuario registrado\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }

        printf("\n\t\t\t\t\t Preciona 'S' para salir o 'A' para actualizar [S/A]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while (respuesta == 'A' || respuesta == 'a');
};

// **********************************************FN13 REGISTRO DE UNA SUCURSAL************************************

struct registroSucursal capturarS()
{

    struct registroSucursal registroSuc;
    struct registroUsuario Usuario;

    FILE *ptrArchivo = NULL;

    int repite = 1, encontrar;
    int existeID, existeSucursal, existeUsuario, modi, enco;
    char ID[50], nombreSucursal[50], nombreUsuario[50], respuesta;

    do
    {
        system(CLEAR);
        tituloAdmin();

        encontrar = 0;
        printf("\n\t\t\t\t\t\t   >> REGISTRAR SUCURSALES <<\n");
        printf("\t\t\t\t\t\t      ====================\n\n");

        do
        {
            existeID = 0;

            printf("\t\t\t\t\t       Introduce ID de sucursal: ");
            scanf(" %[^\n]%*c", ID);

            ptrArchivo = fopen("Sucursales.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registroSuc, sizeof(registroSuc), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registroSuc.id, ID) == 0)
                    {
                        existeID = 1;
                        break;
                    }
                    fread(&registroSuc, sizeof(registroSuc), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (existeID == 1)
            {
                printf("\n\t\t\t\t\tEl  ID %s ya ha sido registrado previamente\n", ID);
                printf("\t\t\t\t\tNo puede registrar dos sucursales con el mismo ID.\n\n\n");
            }

        } while (existeID == 1);

        do
        {
            existeSucursal = 0;

            printf("\t\t\t\t\t       Introduce nombre de sucursal: ");
            scanf("%[^\n]%*c", nombreSucursal);

            ptrArchivo = fopen("Sucursales.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registroSuc, sizeof(registroSuc), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registroSuc.nombre, nombreSucursal) == 0)
                    {
                        existeSucursal = 1;
                        break;
                    }
                    fread(&registroSuc, sizeof(registroSuc), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (existeSucursal == 1)
            {
                printf("\n\t\t\t\t\tLa  sucursal %s ya ha sido registrada previamente\n", nombreSucursal);
                printf("\t\t\t\t\tNo puede registrar dos sucursales con el mismo nombre.\n\n\n");
            }

        } while (existeSucursal == 1);

        ptrArchivo = fopen("Usuarios.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t                    ==> USUARIOS REGISTRADOS <==\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s\n", "ID", "USUARIO", "PASSWORD", "SUCURSAL");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&Usuario, sizeof(Usuario), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {
                printf("\t\t  %10s", Usuario.id);
                printf("%25s", Usuario.usuario);
                printf("%25s", Usuario.password);
                printf("%25s", Usuario.sucursal);
                printf("\n");

                fread(&Usuario, sizeof(Usuario), 1, ptrArchivo);
            }
        }
        else
        {
            printf("\t\t No existen usuarios registrados\n");
        }

        printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

        fclose(ptrArchivo);

        do
        {
            existeUsuario = 0;
            modi = 0;
            enco = 0;

            printf("\n\t\t\t\t\t       Introduce nombre de encargado: ");
            scanf("%[^\n]%*c", nombreUsuario);

            ptrArchivo = fopen("Usuarios.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&Usuario, sizeof(Usuario), 1, ptrArchivo);
                while (!feof(ptrArchivo) && existeUsuario == 0)
                {
                    if (strcmp(Usuario.usuario, nombreUsuario) == 0)
                    {
                        existeUsuario = 1;
                        break;
                    }
                    fread(&Usuario, sizeof(Usuario), 1, ptrArchivo);
                }
            }
            fclose(ptrArchivo);

            if (existeUsuario == 0)
            {
                printf("\n\t\tEl usuario %s no existe\n", nombreUsuario);
                printf("%s\n", Usuario.usuario);
                printf("\n\n\n");
            }

            if (existeUsuario == 1)
            {
                ptrArchivo = fopen("Usuarios.dat", "r+b");

                if (ptrArchivo != NULL)
                {
                    fread(&Usuario, sizeof(Usuario), 1, ptrArchivo);
                    while (!feof(ptrArchivo) && enco == 0)
                    {
                        if (strcmp(Usuario.usuario, nombreUsuario) == 0)
                        {

                            long pos = ftell(ptrArchivo) - sizeof(Usuario);
                            fseek(ptrArchivo, pos, SEEK_SET);
                            strcpy(Usuario.sucursal, nombreSucursal);
                            fwrite(&Usuario, sizeof(Usuario), 1, ptrArchivo);
                            printf("\n\t\tDatos actualizados correctamente\n\n");
                            modi = 1;
                            enco = 1;
                        }
                        fread(&Usuario, sizeof(Usuario), 1, ptrArchivo);
                    }
                    fclose(ptrArchivo);
                }
            }

        } while (existeUsuario == 0 && modi == 0);

        if (existeSucursal == 0)
        {

            strcpy(registroSuc.id, ID);
            strcpy(registroSuc.nombre, nombreSucursal);

            printf("\t\t\t\t\t       Introduce direccion de sucursal: ");
            scanf("%[^\n]%*c", registroSuc.direccion);

            strcpy(registroSuc.encargado, nombreUsuario);
        }

        if (ptrArchivo != NULL || ptrArchivo == NULL)
        {
            ptrArchivo = fopen("Sucursales.dat", "ab");
            if (ptrArchivo != NULL)
            {
                fwrite(&registroSuc, sizeof(registroSuc), 1, ptrArchivo);
                printf("\n\n\t\t\t\t\t        Sucursal creada correctamente\n\n");
            }
            fclose(ptrArchivo);
        }
        else
        {
            printf("\n\n\t\t\t\t\t Sucursal no creada");
        }

        printf("\n\t\t\t\t\t Desea seguir registrando sucursales? [S/N]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while (respuesta == 'S' || respuesta == 's');
};

// **********************************************FN17 ELIMINAR UNA SUCURSAL************************************

struct registroSucursal eliminarS()
{

    struct registroSucursal eSucursal;

    FILE *ptrArchivo = NULL;

    int encontrar, elimina;
    char repite = 1, respuesta, idSuc[50];

    do
    {
        elimina = 0;
        encontrar = 0;
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t>> ELIMINAR SUCURSAL POR CODIGO <<\n");
        printf("\t\t\t\t\t\t   ============================\n\n");

        ptrArchivo = fopen("Sucursales.dat", "r+b");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese la clave de la sucursal: ");
            scanf(" %[^\n]%*c", idSuc);
            printf("\n");

            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n");
            printf("\t%10s%25s%40s%25s\n", "ID", "NOMBRE", "DIRECCION", "ENCARGADO");
            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&eSucursal, sizeof(eSucursal), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {

                if (strcmp(eSucursal.id, idSuc) == 0)
                {
                    encontrar = 1;

                    printf("\t%10s", eSucursal.id);
                    printf("%25s", eSucursal.nombre);
                    printf("%40s", eSucursal.direccion);
                    printf("%25s", eSucursal.encargado);
                    printf("\n");

                    printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                    printf("\n\t\t\t\t\t Esta seguro de querer eliminar esta sucursal? [S/N]: ");
                    scanf("%s%*c", &respuesta);

                    if (respuesta == 'S' || respuesta == 's')
                    {

                        long pos = ftell(ptrArchivo) - sizeof(eSucursal);
                        fseek(ptrArchivo, pos, SEEK_SET);
                        strcpy(eSucursal.id, VALOR_CENTINELA);
                        fwrite(&eSucursal, sizeof(eSucursal), 1, ptrArchivo);
                        printf("\n\t\t\t\t\t          Sucursal eliminada correctamente\n\n");

                        elimina = 1;

                        break;
                    }
                }

                fread(&eSucursal, sizeof(eSucursal), 1, ptrArchivo);
            }
        }

        fclose(ptrArchivo);

        if (idSuc != eSucursal.id && encontrar == 0 && elimina == 0)
        {
            printf("\t No existe ninguna sucursal con esta clave\n");
            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            printf("\n\t\t\t\t\t Desea ingresar una clave valida de sucursal? [S/N]: ");
        }
        if (elimina == 1)
        {
            printf("\n\t\t\t\t\t        Desea eliminar otra sucursal? [S/N]: ");
            scanf("%s%*c", &respuesta);
        }
        printf("\n");

    } while ((respuesta == 'S' || respuesta == 's'));

    eliminarFisicaS();
}

struct registroSucursal eliminarFisicaS()
{

    struct registroSucursal eFisicaS;

    FILE *ptrArchivo = NULL;
    FILE *temporal = NULL;

    char elimina = 0;

    ptrArchivo = fopen("Sucursales.dat", "rb");
    temporal = fopen("Temporal.dat", "wb");

    if (ptrArchivo != NULL || temporal != NULL)
    {
        fread(&eFisicaS, sizeof(eFisicaS), 1, ptrArchivo);
        while (!feof(ptrArchivo))
        {
            if (strcmp(eFisicaS.id, VALOR_CENTINELA) != 0)
            {
                fwrite(&eFisicaS, sizeof(eFisicaS), 1, temporal);
            }
            fread(&eFisicaS, sizeof(eFisicaS), 1, ptrArchivo);
        }
        fclose(ptrArchivo);
        fclose(temporal);

        remove("Sucursales.dat");
        rename("Temporal.dat", "Sucursales.dat");

        elimina = 1;
    }
}

// ____________________________________FN14 MODIFICAR UNA SUCURSAL_________________________________________

struct registroSucursal modificarS()
{

    struct registroSucursal mSucursal;

    FILE *ptrArchivo = NULL;

    int modificado = 0;
    int existe = 0;
    int encontrar, opcion, existeSuc;
    char codigo[50], respuesta, nombreSucursal[50];

    do
    {
        encontrar = 0;
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t>> MODIFICAR SUCURSALES POR CODIGO <<\n");
        printf("\t\t\t\t\t\t   ===============================\n\n");

        ptrArchivo = fopen("Sucursales.dat", "r+b");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese la clave de la sucursal: ");
            scanf(" %[^\n]%*c", codigo);
            printf("\n");

            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n");
            printf("\t%10s%25s%40s%25s\n", "ID", "NOMBRE", "DIRECCION", "ENCARGADO");
            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&mSucursal, sizeof(mSucursal), 1, ptrArchivo);
            while (!feof(ptrArchivo) && encontrar == 0)
            {

                if (strcmp(codigo, mSucursal.id) == 0)
                {
                    printf("\t%10s", mSucursal.id);
                    printf("%25s", mSucursal.nombre);
                    printf("%40s", mSucursal.direccion);
                    printf("%25s", mSucursal.encargado);
                    printf("\n");

                    printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                    do
                    {

                        printf("\n\t\t\t\t\t\t     [1]. Todos los registros\n");
                        printf("\t\t\t\t\t\t     [2]. Nombre\n");
                        printf("\t\t\t\t\t\t     [3]. Direccion\n");
                        printf("\t\t\t\t\t\t     [4]. Encargado\n");
                        printf("\t\t\t\t\t\t     [5]. Volver\n");
                        printf("\n");
                        printf("\t\t\t\t\t   Introduce la opcion que deseas ejecutar: [ ]\b\b");
                        scanf("%d%*c\0", &opcion);

                        switch (opcion)
                        {

                        case 1:

                            printf("\n\t\t\t\t\t   Modificar todos los registros de la sucursal\n\n");

                            printf("\t\t\t\t\t        ID: %s\n", mSucursal.id);

                            printf("\t\t\t\t\t        NOMBRE: ");
                            scanf("%[^\n]%*c", mSucursal.nombre);

                            printf("\t\t\t\t\t        DIRECCION: ");
                            scanf("%[^\n]%*c", mSucursal.direccion);

                            printf("\t\t\t\t\t        ENCARGADO: ");
                            scanf("%[^\n]%*c", mSucursal.encargado);

                            long pos = ftell(ptrArchivo) - sizeof(mSucursal);
                            fseek(ptrArchivo, pos, SEEK_SET);
                            fwrite(&mSucursal, sizeof(mSucursal), 1, ptrArchivo);
                            system(CLEAR);
                            tituloAdmin();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 2:

                            printf("\n\t\t\t\t\t   Modificar registro de sucursal\n\n");

                            printf("\t\t\t\t\t        ID: %s\n", mSucursal.id);

                            printf("\t\t\t\t\t        NOMBRE: ");
                            scanf("%[^\n]%*c", mSucursal.nombre);

                            long pos1 = ftell(ptrArchivo) - sizeof(mSucursal);
                            fseek(ptrArchivo, pos1, SEEK_SET);
                            fwrite(&mSucursal, sizeof(mSucursal), 1, ptrArchivo);
                            system(CLEAR);
                            tituloAdmin();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 3:

                            printf("\n\t\t\t\t\t   Modificar registro de sucursal\n\n");

                            printf("\t\t\t\t\t        ID: %s\n", mSucursal.id);

                            printf("\t\t\t\t\t        DIRECCION: ");
                            scanf("%[^\n]%*c", mSucursal.direccion);

                            long pos2 = ftell(ptrArchivo) - sizeof(mSucursal);
                            fseek(ptrArchivo, pos2, SEEK_SET);
                            fwrite(&mSucursal, sizeof(mSucursal), 1, ptrArchivo);
                            system(CLEAR);
                            tituloAdmin();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 4:

                            printf("\n\t\t\t\t\t   Modificar registro de sucursal\n\n");

                            printf("\t\t\t\t\t        ID: %s\n", mSucursal.id);

                            printf("\t\t\t\t\t        ENCARGADO: ");
                            scanf("%[^\n]%*c", mSucursal.encargado);

                            long pos3 = ftell(ptrArchivo) - sizeof(mSucursal);
                            fseek(ptrArchivo, pos3, SEEK_SET);
                            fwrite(&mSucursal, sizeof(mSucursal), 1, ptrArchivo);
                            system(CLEAR);
                            tituloAdmin();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 5:
                            menuSucursal();
                            break;

                        default:
                            printf("\n\t\t\t\t\t        La opcion no existe, intentelo de nuevo\n\n");
                            modificado = 0;
                            break;
                        }

                        if (modificado == 1)
                        {
                            printf("\n\t\t\t\t\t           ==> SUCURSAL MODIFICADA <==\n");
                            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n");
                            printf("\t%10s%25s%40s%25s\n", "ID", "NOMBRE", "DIRECCION", "ENCARGADO");
                            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                            printf("\t%10s", mSucursal.id);
                            printf("%25s", mSucursal.nombre);
                            printf("%40s", mSucursal.direccion);
                            printf("%25s", mSucursal.encargado);

                            printf(ANSI_COLOR_YELLOW "\n\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
                        }

                    } while (modificado == 0);
                }

                fread(&mSucursal, sizeof(mSucursal), 1, ptrArchivo);
            }
        }

        fclose(ptrArchivo);

        if (codigo != mSucursal.id && modificado == 0)
        {
            printf("\t No existe ninguna sucursal con esta clave\n");
            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            printf("\n\t\t\t\t\t     Desea intentarlo de nuevo? [S/N]: ");
            scanf("%s%*c", &respuesta);
        }

        if (modificado == 1)
        {
            printf("\n\t\t\t\t\t        Desea modificar otra sucursal? [S/N]: ");
            scanf("%s%*c", &respuesta);

            printf("\n");
        }

    } while (respuesta == 'S' || respuesta == 's');
};

// ____________________________________FN15 CONSULTAR UNA SUCURSAL________________________________________

struct registroSucursal consultarS()
{

    struct registroSucursal cSucursal;

    FILE *ptrArchivo = NULL;

    char codigo[50], respuesta, respuesta2;
    int encontrar, cont;

    do
    {
        encontrar = 0;
        cont = 0;
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t>> CONSULTAR SUCURSALES POR CODIGO <<\n");
        printf("\t\t\t\t\t\t   ===============================\n\n");

        ptrArchivo = fopen("Sucursales.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese la clave de la sucursal: ");
            scanf(" %[^\n]%*c", codigo);
            printf("\n");

            printf("\n\t\t\t\t                     ==> SUCURSAL REGISTRADA <==\n");
            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n");
            printf("\t   %10s%25s%40s%25s\n", "ID", "NOMBRE", "DIRECCION", "ENCARGADO");
            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&cSucursal, sizeof(cSucursal), 1, ptrArchivo);
            while (!feof(ptrArchivo) && encontrar == 0)
            {
                if (strcmp(codigo, cSucursal.id) == 0)
                {
                    printf("\t  %10s", cSucursal.id);
                    printf("%25s", cSucursal.nombre);
                    printf("%40s", cSucursal.direccion);
                    printf("%25s", cSucursal.encargado);
                    printf("\n");

                    encontrar = 1;
                    cont++;
                }

                fread(&cSucursal, sizeof(cSucursal), 1, ptrArchivo);
            }

            if (encontrar == 0 && cont != 0)
            {
                printf("\t No existe ninguna sucursal con esta clave\n");
            }
            if (cont == 0)
            {
                printf("\t No existe ninguna sucursal registrada\n");
            }
            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }

        fclose(ptrArchivo);

        printf("\n\t\t\t\t\t        Desea consultar otra sucursal? [S/N]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while ((respuesta == 'S' || respuesta == 's'));
};

// ____________________________________FN16 CONSULTAR TODAS LAS SUCURSALES_________________________________

struct registroSucursal consultarTodasSucursales()
{

    struct registroSucursal consultaSucursales;

    FILE *ptrArchivo = NULL;

    int cont = 0;
    char respuesta;

    do
    {

        system(CLEAR);
        tituloAdmin();

        ptrArchivo = fopen("Sucursales.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t               ==> SUCURSALES REGISTRADAS <==\n");
            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n");
            printf("\t%10s%25s%40s%25s\n", "ID", "NOMBRE", "DIRECCION", "ENCARGADO");
            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&consultaSucursales, sizeof(consultaSucursales), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {
                printf("\t%10s", consultaSucursales.id);
                printf("%25s", consultaSucursales.nombre);
                printf("%40s", consultaSucursales.direccion);
                printf("%25s", consultaSucursales.encargado);
                printf("\n");

                cont++;

                fread(&consultaSucursales, sizeof(consultaSucursales), 1, ptrArchivo);
            }
            if (cont == 0)
            {
                printf("\t\t   No existen Sucursales registradas\n\n");
            }

            printf(ANSI_COLOR_YELLOW "\t ----------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }

        fclose(ptrArchivo);

        printf("\n\t\t\t\t   Preciona 'S' para salir o 'A' para actualizar? [S/A]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while (respuesta == 'A' || respuesta == 'a');
};

// ****************************************FN2 REGISTRO DE PRODUCTOS***************************************

struct registroProductos capturarP1()
{

    int i, idExistente, nombreExistente;
    char id[50], marca2[50][50], categoria2[50][50], nombreDelProducto[100], archivo[20], nombreArchivo[50];
    struct registroProductos registrarUnProducto;

    FILE *ptrArchivo = NULL;

    for (i = 0; i < 1; i++)
    {

        do
        {
            system(CLEAR);
            tituloEncargado();

            printf("\n\t\t\t\t\t\t    >> REGISTRAR PRODUCTOS <<\n");
            printf("\t\t\t\t\t\t       ===================\n\n");

            idExistente = 0;

            printf("\n\t\t\t\t\t\tIntroduce el ID del producto: ");
            scanf(" %[^\n]%*c", id);

            ptrArchivo = fopen("Inventario1.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registrarUnProducto.idProducto, id) == 0)
                    {
                        idExistente = 1;
                        break;
                    }
                    fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (idExistente == 1)
            {
                printf("\n\t\t\t\t\t\tEl  ID %s ya ha sido registrado previamente\n", id);
                printf("\n\t\t\t\t\t\tNo puede registrar dos productos con el mismo ID.\n");
            }

        } while (idExistente == 1);

        do
        {
            nombreExistente = 0;

            printf("\t\t\t\t\t\tIntroduce el nombre del producto: ");
            scanf("%[^\n]%*c", nombreDelProducto);

            ptrArchivo = fopen("Inventario1.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registrarUnProducto.nombreProducto, nombreDelProducto) == 0)
                    {

                        nombreExistente = 1;
                        break;
                    }
                    fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (nombreExistente == 1)
            {
                printf("\n\t\t\t\t\t\tEl producto %s ya ha sido registrado previamente\n", nombreDelProducto);
                printf("No puede registrar dos productos con el mismo nombre.\n\n");
            }

        } while (nombreExistente == 1);

        if (nombreExistente == 0)
        {

            strcpy(registrarUnProducto.idProducto, id);
            strcpy(registrarUnProducto.nombreProducto, nombreDelProducto);
        }

        printf("\t\t\t\t\t\tIntroduce la marca del producto: ");
        scanf("%[^\n]%*c", registrarUnProducto.marcaProducto);
        strcpy(marca2[i], registrarUnProducto.marcaProducto);

        do
        {
            printf("\n\t\t\t\t\t\t    ==> OPCIONES A ELEGIR <== ");
            printf("\n\t\t\t\t\t\t   [1]. Cosmetico \n\t\t\t\t\t\t   [2]. Ropa \n\t\t\t\t\t\t   [3]. Accesorios \n\t\t\t\t\t\t   [4]. Bolsas y mochilas");
            printf("\n\n\n\n\t\t\t\t\t\tIntroduce la categoria del producto: [ ]\b\b");
            scanf("%d%*c\0", &registrarUnProducto.categoriaProducto);
            printf("\n");

            if (registrarUnProducto.categoriaProducto != 1 && registrarUnProducto.categoriaProducto != 2 && registrarUnProducto.categoriaProducto != 3 && registrarUnProducto.categoriaProducto != 4)
            {
                printf(ANSI_COLOR_RED "\n\t\t\t\t\t\tERROR" ANSI_COLOR_RESET);
                printf("\n\t\t\t\t\t\tINGRESA UN NÚMERO VÁLIDO\n");
            }

        } while (registrarUnProducto.categoriaProducto != 1 && registrarUnProducto.categoriaProducto != 2 && registrarUnProducto.categoriaProducto != 3 && registrarUnProducto.categoriaProducto != 4);

        printf("\t\t\t\t\t\tPrecio de compra del producto: ");
        scanf("%f%*c", &registrarUnProducto.precioCompra);

        printf("\t\t\t\t\t\tPrecio de venta del producto: ");
        scanf("%f%*c", &registrarUnProducto.precioVenta);

        printf("\t\t\t\t\t\tNumero de existencias del producto: ");
        scanf("%d%*c", &registrarUnProducto.existencia);
    }

    ptrArchivo = fopen("Inventario1.dat", "ab");

    if (ptrArchivo != NULL)
    {
        fwrite(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
        printf(ANSI_COLOR_GREEN "\n\t\t\t\t\t\tProducto registrado correctamente\n" ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_RED "\n\t\t\t\t\t\tError al registrar el producto\n" ANSI_COLOR_RESET);
    }
    fclose(ptrArchivo);

    return (registrarUnProducto);
};

struct registroProductos capturarP2()
{

    int i, idExistente, nombreExistente;
    char id[50], marca2[50][50], categoria2[50][50], nombreDelProducto[100], archivo[20], nombreArchivo[50];
    struct registroProductos registrarUnProducto;

    FILE *ptrArchivo = NULL;

    for (i = 0; i < 1; i++)
    {

        do
        {

            idExistente = 0;

            printf("\n\t\t\t\t\t\tIntroduce el ID del producto: ");
            scanf(" %[^\n]%*c", id);

            ptrArchivo = fopen("Inventario2.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registrarUnProducto.idProducto, id) == 0)
                    {
                        idExistente = 1;
                        break;
                    }
                    fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (idExistente == 1)
            {
                printf("\n\t\t\t\t\t\tEl  ID %s ya ha sido registrado previamente\n", id);
                printf("No puede registrar dos productos con el mismo ID.\n");
            }

        } while (idExistente == 1);

        do
        {
            nombreExistente = 0;

            printf("\n\t\t\t\t\t\tIntroduce el nombre del producto: ");
            scanf("%[^\n]%*c", nombreDelProducto);

            ptrArchivo = fopen("Inventario2.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registrarUnProducto.nombreProducto, nombreDelProducto) == 0)
                    {

                        nombreExistente = 1;
                        break;
                    }
                    fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (nombreExistente == 1)
            {
                printf("\n\t\t\t\t\t\tEl producto %s ya ha sido registrado previamente\n", nombreDelProducto);
                printf("\n\t\t\t\t\t\tNo puede registrar dos productos con el mismo nombre.\n\n");
            }

        } while (nombreExistente == 1);

        if (nombreExistente == 0)
        {

            strcpy(registrarUnProducto.idProducto, id);
            strcpy(registrarUnProducto.nombreProducto, nombreDelProducto);
        }

        printf("\n\t\t\t\t\t\tIntroduce la marca del producto: ");
        scanf("%[^\n]%*c", registrarUnProducto.marcaProducto);
        strcpy(marca2[i], registrarUnProducto.marcaProducto);

        do
        {
            printf("\n\t\t\t\t\t\t =====> OPCIONES A ELEGIR <===== ");
            printf("\n\t\t\t\t\t\t1.- Cosmetico. \n\t\t\t\t\t\t2.- Ropa. \n\t\t\t\t\t\t3.- Accesorios. \n\t\t\t\t\t\t4.- Bolsas y mochilas");
            printf("\n\t\t\t\t\t\tIntroduce la categoria del producto: ");
            scanf("%d%*c", &registrarUnProducto.categoriaProducto);
            printf("\n");

            if (registrarUnProducto.categoriaProducto != 1 && registrarUnProducto.categoriaProducto != 2 && registrarUnProducto.categoriaProducto != 3 && registrarUnProducto.categoriaProducto != 4)
            {
                printf(ANSI_COLOR_RED "\n\t\t\t\t\t\tERROR" ANSI_COLOR_RESET);
                printf("\n\t\t\t\t\t\tINGRESA UN NÚMERO VÁLIDO\n");
            }

        } while (registrarUnProducto.categoriaProducto != 1 && registrarUnProducto.categoriaProducto != 2 && registrarUnProducto.categoriaProducto != 3 && registrarUnProducto.categoriaProducto != 4);

        printf("\n\t\t\t\t\t\tPrecio de compra del producto: ");
        scanf("%f%*c", &registrarUnProducto.precioCompra);

        printf("\n\t\t\t\t\t\tPrecio de venta del producto: ");
        scanf("%f%*c", &registrarUnProducto.precioVenta);

        printf("\n\t\t\t\t\t\tNumero de existencias del producto: ");
        scanf("%d%*c", &registrarUnProducto.existencia);
    }

    ptrArchivo = fopen("Inventario2.dat", "ab");

    if (ptrArchivo != NULL)
    {
        fwrite(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
        printf(ANSI_COLOR_GREEN "\n\t\t\t\t\t\tProducto ingresado correctamente\n" ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_RED "\n\t\t\t\t\t\tError al introducir el producto\n" ANSI_COLOR_RESET);
    }
    fclose(ptrArchivo);

    return (registrarUnProducto);
};

struct registroProductos capturarP3()
{

    int i, idExistente, nombreExistente;
    char id[50], marca2[50][50], categoria2[50][50], nombreDelProducto[100], archivo[20], nombreArchivo[50];
    struct registroProductos registrarUnProducto;

    FILE *ptrArchivo = NULL;

    for (i = 0; i < 1; i++)
    {

        do
        {

            idExistente = 0;

            printf("\n\t\t\t\t\t\tIntroduce el ID del producto: ");
            scanf(" %[^\n]%*c", id);

            ptrArchivo = fopen("Inventario3.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registrarUnProducto.idProducto, id) == 0)
                    {
                        idExistente = 1;
                        break;
                    }
                    fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (idExistente == 1)
            {
                printf("\n\t\t\t\t\t\tEl  ID %s ya ha sido registrado previamente\n", id);
                printf("No puede registrar dos productos con el mismo ID.\n");
            }

        } while (idExistente == 1);

        do
        {
            nombreExistente = 0;

            printf("\n\t\t\t\t\t\tIntroduce el nombre del producto: ");
            scanf("%[^\n]%*c", nombreDelProducto);

            ptrArchivo = fopen("Inventario3.dat", "rb");

            if (ptrArchivo != NULL)
            {
                fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                while (!feof(ptrArchivo))
                {
                    if (strcmp(registrarUnProducto.nombreProducto, nombreDelProducto) == 0)
                    {

                        nombreExistente = 1;
                        break;
                    }
                    fread(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }

            if (nombreExistente == 1)
            {
                printf("\n\t\t\t\t\t\tEl producto %s ya ha sido registrado previamente\n", nombreDelProducto);
                printf("\n\t\t\t\t\t\tNo puede registrar dos productos con el mismo nombre.\n\n");
            }

        } while (nombreExistente == 1);

        if (nombreExistente == 0)
        {

            strcpy(registrarUnProducto.idProducto, id);
            strcpy(registrarUnProducto.nombreProducto, nombreDelProducto);
        }

        printf("\n\t\t\t\t\t\tIntroduce la marca del producto: ");
        scanf("%[^\n]%*c", registrarUnProducto.marcaProducto);
        strcpy(marca2[i], registrarUnProducto.marcaProducto);

        do
        {
            printf("\n\t\t\t\t\t\t =====> OPCIONES A ELEGIR <===== ");
            printf("\n\t\t\t\t\t\tn1.- Cosmetico. \n\t\t\t\t\t\t2.- Ropa. \n\t\t\t\t\t\t3.- Accesorios. \n\t\t\t\t\t\t4.- Bolsas y mochilas");
            printf("\n\t\t\t\t\t\tIntroduce la categoria del producto: ");
            scanf("%d%*c", &registrarUnProducto.categoriaProducto);
            printf("\n");

            if (registrarUnProducto.categoriaProducto != 1 && registrarUnProducto.categoriaProducto != 2 && registrarUnProducto.categoriaProducto != 3 && registrarUnProducto.categoriaProducto != 4)
            {
                printf(ANSI_COLOR_RED "\n\t\t\t\t\t\tERROR" ANSI_COLOR_RESET);
                printf("\n\t\t\t\t\t\tINGRESA UN NUMERO VALIDO\n");
            }

        } while (registrarUnProducto.categoriaProducto != 1 && registrarUnProducto.categoriaProducto != 2 && registrarUnProducto.categoriaProducto != 3 && registrarUnProducto.categoriaProducto != 4);

        printf("\n\t\t\t\t\t\tPrecio de compra del producto: ");
        scanf("%f%*c", &registrarUnProducto.precioCompra);

        printf("\n\t\t\t\t\t\tPrecio de venta del producto: ");
        scanf("%f%*c", &registrarUnProducto.precioVenta);

        printf("\n\t\t\t\t\t\tNumero de existencias del producto: ");
        scanf("%d%*c", &registrarUnProducto.existencia);
    }

    ptrArchivo = fopen("Inventario3.dat", "ab");

    if (ptrArchivo != NULL)
    {
        fwrite(&registrarUnProducto, sizeof(registrarUnProducto), 1, ptrArchivo);
        printf(ANSI_COLOR_GREEN "\n\t\t\t\t\t\tProducto ingresado correctamente\n" ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_RED "\n\t\t\t\t\t\tError al ingresar el producto" ANSI_COLOR_RESET);
    }
    fclose(ptrArchivo);

    return (registrarUnProducto);
};

// **********************************************FN9 ELIMINAR UN PRODUCTO************************************

struct registroProductos eliminarP()
{

    struct registroProductos eProducto;

    FILE *ptrArchivo = NULL;

    int encontrar, elimina;
    char repite = 1, respuesta, idProduct[50];

    do
    {
        elimina = 0;
        encontrar = 0;
        system(CLEAR);
        tituloEncargado();

        printf("\n\t\t\t\t\t\t>> ELIMINAR PRODUCTO POR CODIGO <<\n");
        printf("\t\t\t\t\t\t   ============================\n\n");

        ptrArchivo = fopen("Inventario1.dat", "r+b");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese la clave del producto: ");
            scanf(" %[^\n]%*c", idProduct);
            printf("\n");

            printf(ANSI_COLOR_YELLOW "      -----------------------------------------------------------------------------------------------------------------------\n");
            printf("%13s%30s%15s%15s%15s%15s%15s\n", "ID", "PRODUCTO", "MARCA", "CATEGORIA", "$ DE COMPRA", "$ DE VENTA", "EXISTENCIA");
            printf(ANSI_COLOR_YELLOW "      -----------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&eProducto, sizeof(eProducto), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {

                if (strcmp(eProducto.idProducto, idProduct) == 0)
                {
                    encontrar = 1;

                    printf("%13s", eProducto.idProducto);
                    printf("%30s", eProducto.nombreProducto);
                    printf("%15s", eProducto.marcaProducto);
                    printf("%15d", eProducto.categoriaProducto);
                    printf("%15.2f", eProducto.precioCompra);
                    printf("%15.2f", eProducto.precioVenta);
                    printf("%15d", eProducto.existencia);
                    printf("\n");

                    printf(ANSI_COLOR_YELLOW "      -----------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                    printf("\n\t\t\t\t\tEsta seguro de querer eliminar este producto? [S/N]: ");
                    scanf("%s", &respuesta);

                    if (respuesta == 'S' || respuesta == 's')
                    {

                        long pos = ftell(ptrArchivo) - sizeof(eProducto);
                        fseek(ptrArchivo, pos, SEEK_SET);
                        strcpy(eProducto.idProducto, VALOR_CENTINELA);
                        fwrite(&eProducto, sizeof(eProducto), 1, ptrArchivo);
                        printf("\n\t\t\t\t\t Producto eliminado correctamente\n\n");

                        elimina = 1;

                        break;
                    }
                }

                fread(&eProducto, sizeof(eProducto), 1, ptrArchivo);
            }
        }

        fclose(ptrArchivo);

        if (idProduct != eProducto.idProducto && encontrar == 0 && elimina == 0)
        {
            printf("      No existe ningun producto con esta clave\n");
            printf(ANSI_COLOR_YELLOW "      -----------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            printf("\n\t\t\t\t\t Desea ingresar una clave valida de producto? [S/N]: ");
            scanf("%s%*c", &respuesta);
        }
        if (elimina == 1)
        {
            printf("\n\t\t\t\t\t Desea eliminar otro producto? [S/N]: ");
            scanf("%s%*c", &respuesta);
        }
        printf("\n");

    } while (respuesta == 'S' || respuesta == 's');

    eliminarFisicaP();
}

struct registroProductos eliminarFisicaP()
{

    struct registroProductos eFisica;

    FILE *ptrArchivo = NULL;
    FILE *temporal = NULL;

    char elimina = 0;

    ptrArchivo = fopen("Inventario1.dat", "rb");
    temporal = fopen("Temporal.dat", "wb");

    if (ptrArchivo != NULL || temporal != NULL)
    {
        fread(&eFisica, sizeof(eFisica), 1, ptrArchivo);
        while (!feof(ptrArchivo))
        {
            if (strcmp(eFisica.idProducto, VALOR_CENTINELA) != 0)
            {
                fwrite(&eFisica, sizeof(eFisica), 1, temporal);
            }
            fread(&eFisica, sizeof(eFisica), 1, ptrArchivo);
        }
        fclose(ptrArchivo);
        fclose(temporal);

        remove("Inventario1.dat");
        rename("Temporal.dat", "Inventario1.dat");

        elimina = 1;
    }
}

// ____________________________________FN6 CONSULTA DE TODOS LOS PRODUCTOS_________________________________

struct registroProductos consultarTodosProductos()
{

    struct registroProductos consultaProducto;

    FILE *ptrArchivo = NULL;

    int cont = 0;
    char respuesta;

    do
    {

        system(CLEAR);
        tituloEncargado();

        ptrArchivo = fopen("Inventario1.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t                    ==> PRODUCTOS REGISTRADOS <==\n");
            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n");
            printf(" %10s%25s%28s%15s%15s%15s%15s\n", "ID", "PRODUCTO", "MARCA", "CATEGORIA", "$ COMPRA", "$ VENTA", "EXISTENCIA");
            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&consultaProducto, sizeof(consultaProducto), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {
                printf("   %10s", consultaProducto.idProducto);
                printf("%25s", consultaProducto.nombreProducto);
                printf("%25s", consultaProducto.marcaProducto);
                printf("%15d", consultaProducto.categoriaProducto);
                printf("%15.2f", consultaProducto.precioCompra);
                printf("%15.2f", consultaProducto.precioVenta);
                printf("%15d", consultaProducto.existencia);
                printf("\n");

                cont++;

                fread(&consultaProducto, sizeof(consultaProducto), 1, ptrArchivo);
            }

            if (cont == 0)
            {
                printf("\t\t   No existen usuarios registrados\n");
            }

            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }

        fclose(ptrArchivo);

        printf("\n\t\t\t\t\t Preciona 'S' para salir o 'A' para actualizar [S/A]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while (respuesta == 'A' || respuesta == 'a');
};

// ____________________________________FN8 CONSULTA DE PRODUCTOS POR CATEGORIA_____________________________

struct registroProductos consultarProductosCategoria()
{

    struct registroProductos consultaCategoria;

    char respuesta;
    int categoriaOpc, encontrar;

    FILE *ptrArchivo = NULL;

    do
    {
        encontrar = 0;
        system(CLEAR);
        tituloEncargado();

        ptrArchivo = fopen("Inventario1.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\t    ==> OPCIONES A ELEGIR <== ");
            printf("\n\t\t\t\t\t\t   [1]. Cosmetico \n\t\t\t\t\t\t   [2]. Ropa \n\t\t\t\t\t\t   [3]. Accesorios \n\t\t\t\t\t\t   [4]. Bolsas y mochilas");
            printf("\n\n\t\t\t\t\t\tIntroduce la categoria del producto: [ ]\b\b");
            scanf("%d%*c\0", &categoriaOpc);
            printf("\n");

            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n");
            printf(" %10s%25s%28s%15s%15s%15s%15s\n", "ID", "PRODUCTO", "MARCA", "CATEGORIA", "$ COMPRA", "$ VENTA", "EXISTENCIA");
            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&consultaCategoria, sizeof(consultaCategoria), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {
                if (categoriaOpc == consultaCategoria.categoriaProducto && consultaCategoria.categoriaProducto == 1)
                {
                    printf("   %10s", consultaCategoria.idProducto);
                    printf("%25s", consultaCategoria.nombreProducto);
                    printf("%25s", consultaCategoria.marcaProducto);
                    printf("%15d", consultaCategoria.categoriaProducto);
                    printf("%15.2f", consultaCategoria.precioCompra);
                    printf("%15.2f", consultaCategoria.precioVenta);
                    printf("%15d", consultaCategoria.existencia);
                    printf("\n");

                    encontrar = 1;
                }

                if (categoriaOpc == consultaCategoria.categoriaProducto && consultaCategoria.categoriaProducto == 2)
                {
                    printf("   %10s", consultaCategoria.idProducto);
                    printf("%25s", consultaCategoria.nombreProducto);
                    printf("%25s", consultaCategoria.marcaProducto);
                    printf("%15d", consultaCategoria.categoriaProducto);
                    printf("%15.2f", consultaCategoria.precioCompra);
                    printf("%15.2f", consultaCategoria.precioVenta);
                    printf("%15d", consultaCategoria.existencia);
                    printf("\n");

                    encontrar = 1;
                }

                if (categoriaOpc == consultaCategoria.categoriaProducto && consultaCategoria.categoriaProducto == 3)
                {
                    printf("   %10s", consultaCategoria.idProducto);
                    printf("%25s", consultaCategoria.nombreProducto);
                    printf("%25s", consultaCategoria.marcaProducto);
                    printf("%15d", consultaCategoria.categoriaProducto);
                    printf("%15.2f", consultaCategoria.precioCompra);
                    printf("%15.2f", consultaCategoria.precioVenta);
                    printf("%15d", consultaCategoria.existencia);
                    printf("\n");

                    encontrar = 1;
                }

                if (categoriaOpc == consultaCategoria.categoriaProducto && consultaCategoria.categoriaProducto == 4)
                {
                    printf("   %10s", consultaCategoria.idProducto);
                    printf("%25s", consultaCategoria.nombreProducto);
                    printf("%25s", consultaCategoria.marcaProducto);
                    printf("%15d", consultaCategoria.categoriaProducto);
                    printf("%15.2f", consultaCategoria.precioCompra);
                    printf("%15.2f", consultaCategoria.precioVenta);
                    printf("%15d", consultaCategoria.existencia);
                    printf("\n");

                    encontrar = 1;
                }

                fread(&consultaCategoria, sizeof(consultaCategoria), 1, ptrArchivo);
            }
            if (encontrar == 1)
            {
                printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            }

            if (encontrar == 0)
            {
                printf(ANSI_COLOR_RED "\t\t\t\t\t\t===== PRODUCTO NO ENCONTRADO =====\n" ANSI_COLOR_RESET);
                printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            }
        }

        fclose(ptrArchivo);

        printf("\n\t\t\t\t\t        Desea consultar otra categoria? [S/N]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while (respuesta == 'S' || respuesta == 's');
};

//_____________________________________Consultar producto en otra sucursal (Encargado)_____________________________________

void productSuc()
{
    consultarProductoSucursales1();
    consultarProductoSucursales2();
    consultarProductoSucursales3();
}

struct registroProductos consultarProductoSucursales1()
{

    struct registroProductos cProductoSucursales;

    FILE *ptrArchivo = NULL;

    char product[50], respuesta;
    int encontrar;

    do
    {

        encontrar = 0;
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t>> CONSULTAR PRODUCTOS POR NOMBRE <<\n");
        printf("\t\t\t\t\t\t   =============================\n\n");

        ptrArchivo = fopen("Inventario1.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese el nombre del producto: ");
            scanf("%*c%[^\n]%*c", product);
            printf("\n");

            printf("\n\t\t\t\t                    ==> USUARIOS REGISTRADOS <==\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s%25s\n", "ID", "NOMBRE", "MARCA", "CATEGORIA", "COMPRA", "VENTA", "EXISTENCIA");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&cProductoSucursales, sizeof(cProductoSucursales), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {

                if (strcmp(product, cProductoSucursales.nombreProducto) == 0)
                {
                    printf("\t\t  %10s", cProductoSucursales.idProducto);
                    printf("%25s", cProductoSucursales.nombreProducto);
                    printf("%25s", cProductoSucursales.marcaProducto);
                    printf("%25s", cProductoSucursales.categoriaProducto);
                    printf("%25s", cProductoSucursales.precioCompra);
                    printf("%25s", cProductoSucursales.precioVenta);
                    printf("%25s", cProductoSucursales.existencia);
                    printf("\n");

                    encontrar = 1;
                }
                fread(&cProductoSucursales, sizeof(cProductoSucursales), 1, ptrArchivo);
            }

            if (encontrar == 0)
            {
                printf("\t\t   No existe ningun producto con este nombre\n");
            }

            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }
        fclose(ptrArchivo);

        printf("\n\t\t\t\t\t        Desea consultar otro producto? [S/N]: ");
        scanf("%s", &respuesta);

        printf("\n");

    } while (respuesta == 'S' || respuesta == 's');

    return (cProductoSucursales);
};

struct registroProductos consultarProductoSucursales2()
{

    struct registroProductos cProductoSucursales;

    FILE *ptrArchivo = NULL;

    char product[50], respuesta;
    int encontrar;

    do
    {

        encontrar = 0;
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t>> CONSULTAR PRODUCTOS POR NOMBRE <<\n");
        printf("\t\t\t\t\t\t   =============================\n\n");

        ptrArchivo = fopen("Inventario2.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese el nombre del producto: ");
            scanf("%*c%[^\n]%*c", product);
            printf("\n");

            printf("\n\t\t\t\t                    ==> USUARIOS REGISTRADOS <==\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s%25s\n", "ID", "NOMBRE", "MARCA", "CATEGORIA", "COMPRA", "VENTA", "EXISTENCIA");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&cProductoSucursales, sizeof(cProductoSucursales), 1, ptrArchivo);
            while (!feof(ptrArchivo) && encontrar == 0)
            {
                if (strcmp(product, cProductoSucursales.nombreProducto) == 0)
                {
                    printf("\t\t  %10s", cProductoSucursales.idProducto);
                    printf("%25s", cProductoSucursales.nombreProducto);
                    printf("%25s", cProductoSucursales.marcaProducto);
                    printf("%25s", cProductoSucursales.categoriaProducto);
                    printf("%25s", cProductoSucursales.precioCompra);
                    printf("%25s", cProductoSucursales.precioVenta);
                    printf("%25s", cProductoSucursales.existencia);
                    printf("\n");

                    encontrar = 1;
                }
                fread(&cProductoSucursales, sizeof(cProductoSucursales), 1, ptrArchivo);
            }

            if (encontrar == 0)
            {
                printf("\t\t   No existe ningun producto con este nombre\n");
            }

            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }
        fclose(ptrArchivo);

        printf("\n\t\t\t\t\t        Desea consultar otro producto? [S/N]: ");
        scanf("%s", &respuesta);

        printf("\n");

    } while (respuesta == 'S' || respuesta == 's');

    return (cProductoSucursales);
};

struct registroProductos consultarProductoSucursales3()
{

    struct registroProductos cProductoSucursales;

    FILE *ptrArchivo = NULL;

    char product[50], respuesta;
    int encontrar;

    do
    {

        encontrar = 0;
        system(CLEAR);
        tituloAdmin();

        printf("\n\t\t\t\t\t\t>> CONSULTAR PRODUCTOS POR NOMBRE <<\n");
        printf("\t\t\t\t\t\t   =============================\n\n");

        ptrArchivo = fopen("Inventario3.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t\t\tIngrese el nombre del producto: ");
            scanf("%*c%[^\n]%*c", product);
            printf("\n");

            printf("\n\t\t\t\t                    ==> USUARIOS REGISTRADOS <==\n");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n");
            printf("\t\t  %10s%25s%25s%25s%25s\n", "ID", "NOMBRE", "MARCA", "CATEGORIA", "COMPRA", "VENTA", "EXISTENCIA");
            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&cProductoSucursales, sizeof(cProductoSucursales), 1, ptrArchivo);
            while (!feof(ptrArchivo) && encontrar == 0)
            {
                if (strcmp(product, cProductoSucursales.nombreProducto) == 0)
                {
                    printf("\t\t  %10s", cProductoSucursales.idProducto);
                    printf("%25s", cProductoSucursales.nombreProducto);
                    printf("%25s", cProductoSucursales.marcaProducto);
                    printf("%25s", cProductoSucursales.categoriaProducto);
                    printf("%25s", cProductoSucursales.precioCompra);
                    printf("%25s", cProductoSucursales.precioVenta);
                    printf("%25s", cProductoSucursales.existencia);
                    printf("\n");

                    encontrar = 1;
                }
                fread(&cProductoSucursales, sizeof(cProductoSucursales), 1, ptrArchivo);
            }

            if (encontrar == 0)
            {
                printf("\t\t   No existe ningun producto con este nombre\n");
            }

            printf(ANSI_COLOR_YELLOW "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }
        fclose(ptrArchivo);

        printf("\n\t\t\t\t\t        Desea consultar otro producto? [S/N]: ");
        scanf("%s", &respuesta);

        printf("\n");

    } while (respuesta == 'S' || respuesta == 's');

    return (cProductoSucursales);
};

// ******************** STRUCT CONSULTAR PRODUCTOS EN OTRA SUCURSAL ********************

struct registroProductos consultaEnSucursal()
{
    int nArchivo;
    char respuesta;
    char nombreArchivo1[] = "Inventario1", nombreArchivo2[] = "Inventario2", nombreArchivo3[] = "Inventario3", dat[] = ".dat", archivo[20];

    struct registroProductos consultaPSucursal;

    FILE *ptrArchivo = NULL;

    do{
        system(CLEAR);
        tituloEncargado();
        nArchivo = menuConsultaInventario();

        if (nArchivo == 1)
        {

            strcpy(archivo, nombreArchivo1);
            strcat(archivo, dat);
        }

        if (nArchivo == 2)
        {

            strcpy(archivo, nombreArchivo2);
            strcat(archivo, dat);
        }

        if (nArchivo == 3)
        {

            strcpy(archivo, nombreArchivo3);
            strcat(archivo, dat);
        }

        ptrArchivo = fopen(archivo, "rb");

        if (ptrArchivo != NULL)
        {

            fread(&consultaPSucursal, sizeof(consultaPSucursal), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {
                printf(ANSI_COLOR_CYAN "\n\t\t\t\t=====================================================\n" ANSI_COLOR_RESET);
                printf("\t\t\t\t\t\t ID PRODUCTO: %s\n", consultaPSucursal.idProducto);
                printf("\t\t\t\t\t\t NOMBRE: %s\n", consultaPSucursal.nombreProducto);
                printf("\t\t\t\t\t\t MARCA: %s\n", consultaPSucursal.marcaProducto);
                printf("\t\t\t\t\t\t CATEGORIA: %d\n", consultaPSucursal.categoriaProducto);
                printf("\t\t\t\t\t\t PRECIO DE COMPRA: %.2f\n", consultaPSucursal.precioCompra);
                printf("\t\t\t\t\t\t PRECIO DE VENTA: %.2f\n", consultaPSucursal.precioVenta);
                printf("\t\t\t\t\t\t NUMERO DE EXISTENCIAS: %d\n", consultaPSucursal.existencia);
                printf(ANSI_COLOR_CYAN "\t\t\t\t======================================================\n\n" ANSI_COLOR_RESET);

                fread(&consultaPSucursal, sizeof(consultaPSucursal), 1, ptrArchivo);
            }
        }

        fclose(ptrArchivo);
        printf("\n\t\t\t\t\t Preciona 'S' para salir o 'A' para actualizar [S/A]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while (respuesta == 'A' || respuesta == 'a');
};

// ____________________________________FN4 MODIFICAR REGISTRO DE UN PRODUCTO_________________________________________

struct registroProductos modificarP()
{

    struct registroProductos mProducto;

    FILE *ptrArchivo = NULL;

    char codigo[50];
    int modificado = 0;
    int existe = 0;
    int encontrar, opcion, nombreExistente;
    char respuesta, nombreDelProducto[100];

    do
    {
        encontrar = 0;
        system(CLEAR);
        tituloEncargado();

        printf("\n\t\t\t\t\t\t>> MODIFICAR PRODUCTOS POR CODIGO <<\n");
        printf("\t\t\t\t\t\t   ==============================\n\n");

        ptrArchivo = fopen("Inventario1.dat", "r+b");

        if (ptrArchivo != NULL)
        {

            printf("\n\t\t\t\t\t\tIngrese el ID del producto a modificar: ");
            scanf(" %[^\n]%*c", codigo);
            printf("\n");

            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n");
            printf(" %10s%25s%28s%15s%15s%15s%15s\n", "ID", "PRODUCTO", "MARCA", "CATEGORIA", "$ COMPRA", "$ VENTA", "EXISTENCIA");
            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&mProducto, sizeof(mProducto), 1, ptrArchivo);
            while (!feof(ptrArchivo) && encontrar == 0)
            {

                if (strcmp(codigo, mProducto.idProducto) == 0)
                {
                    printf("   %10s", mProducto.idProducto);
                    printf("%25s", mProducto.nombreProducto);
                    printf("%25s", mProducto.marcaProducto);
                    printf("%15d", mProducto.categoriaProducto);
                    printf("%15.2f", mProducto.precioCompra);
                    printf("%15.2f", mProducto.precioVenta);
                    printf("%15d", mProducto.existencia);
                    printf("\n");

                    printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                    do
                    {
                        printf("\n\t\t\t\t\t\t     [1]. Todos los registros\n");
                        printf("\t\t\t\t\t\t     [2]. Producto\n");
                        printf("\t\t\t\t\t\t     [3]. Marca\n");
                        printf("\t\t\t\t\t\t     [4]. Categoria\n");
                        printf("\t\t\t\t\t\t     [5]. Precio compra\n");
                        printf("\t\t\t\t\t\t     [6]. Precio venta\n");
                        printf("\t\t\t\t\t\t     [7]. Numero de existencias\n");
                        printf("\t\t\t\t\t\t     [0]. Volver\n");
                        printf("\n");
                        printf("\t\t\t\t\t   Introduce el registro que deseas modificar: [ ]\b\b");
                        scanf("%d%*c\0", &opcion);

                        switch (opcion)
                        {

                        case 1:

                            printf("\n\t\t\t\t\t\tModificar todos los registros del producto\n\n");

                            printf("\n\t\t\t\t\t\tPRODUCTO: ");
                            scanf("%[^\n]%*c", mProducto.nombreProducto);

                            printf("\n\t\t\t\t\t\tMARCA: ");
                            scanf("%s%*c", mProducto.marcaProducto);

                            do
                            {
                                printf("\n\t\t\t\t\t\t ***** OPCIONES A ELEGIR ***** ");
                                printf("\n\t\t\t\t\t\t1.- Cosmetico. \n\t\t\t\t\t\t2.- Ropa. \n\t\t\t\t\t\t3.- Accesorios. \n\t\t\t\t\t\t4.- Bolsas y mochilas");
                                printf("\n\t\t\t\t\t\tIntroduce la categoria del producto: ");
                                scanf("%d%*c", &mProducto.categoriaProducto);
                                printf("\n");

                                if (mProducto.categoriaProducto != 1 && mProducto.categoriaProducto != 2 && mProducto.categoriaProducto != 3 && mProducto.categoriaProducto != 4)
                                {
                                    printf(ANSI_COLOR_RED "\n\t\t\t\t\t\tERROR" ANSI_COLOR_RESET);
                                    printf("\n\t\t\t\t\t\tINGRESA UN NUMERO VALIDO\n");
                                }

                            } while (mProducto.categoriaProducto != 1 && mProducto.categoriaProducto != 2 && mProducto.categoriaProducto != 3 && mProducto.categoriaProducto != 4);

                            printf("\n\t\t\t\t\t\t$ COMPRA: ");
                            scanf("%f%*c", &mProducto.precioCompra);

                            printf("\n\t\t\t\t\t\t$ VENTA: ");
                            scanf("%f%*c", &mProducto.precioVenta);

                            printf("\n\t\t\t\t\t\tEXISTENCIAS: ");
                            scanf("%d%*c", &mProducto.existencia);

                            long pos = ftell(ptrArchivo) - sizeof(mProducto);
                            fseek(ptrArchivo, pos, SEEK_SET);
                            fwrite(&mProducto, sizeof(mProducto), 1, ptrArchivo);
                            system(CLEAR);
                            tituloEncargado();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 2:

                            printf("\n\t\t\t\t\t\tModificar nombre de producto\n\n");

                            printf("\n\t\t\t\t\t\tID: %s\n", mProducto.idProducto);

                            printf("\n\t\t\t\t\t\tPRODUCTO: ");
                            scanf("%[^\n]%*c", mProducto.nombreProducto);

                            long pos1 = ftell(ptrArchivo) - sizeof(mProducto);
                            fseek(ptrArchivo, pos1, SEEK_SET);
                            fwrite(&mProducto, sizeof(mProducto), 1, ptrArchivo);
                            system(CLEAR);
                            tituloEncargado();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 3:

                            printf("\n\t\t\t\t\t\tModificar marca de producto\n\n");

                            printf("\n\t\t\t\t\t\tID: %s\n", mProducto.idProducto);

                            printf("\n\t\t\t\t\t\tMARCA: ");
                            scanf("%s%*c", mProducto.marcaProducto);

                            long pos2 = ftell(ptrArchivo) - sizeof(mProducto);
                            fseek(ptrArchivo, pos2, SEEK_SET);
                            fwrite(&mProducto, sizeof(mProducto), 1, ptrArchivo);
                            system(CLEAR);
                            tituloEncargado();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 4:

                            printf("\n\t\t\t\t\t\tModificar categoria de producto\n\n");

                            printf("\n\t\t\t\t\t\tID: %s\n", mProducto.idProducto);

                            do
                            {
                                printf("\n\t\t\t\t\t\t =====> OPCIONES A ELEGIR <===== ");
                                printf("\n\t\t\t\t\t\t   [1]. Cosmetico \n\t\t\t\t\t\t   [2]. Ropa \n\t\t\t\t\t\t   [3]. Accesorios \n\t\t\t\t\t\t   [4]. Bolsas y mochilas\n");
                                printf("\n\t\t\t\t\t\tCATEGORIA: ");
                                scanf("%d%*c", &mProducto.categoriaProducto);
                                printf("\n");

                                if (mProducto.categoriaProducto != 1 && mProducto.categoriaProducto != 2 && mProducto.categoriaProducto != 3 && mProducto.categoriaProducto != 4)
                                {
                                    printf(ANSI_COLOR_RED "\n\t\t\t\t\t\tERROR" ANSI_COLOR_RESET);
                                    printf("\n\t\t\t\t\t\tINGRESA UN NUMERO VALIDO\n");
                                }

                            } while (mProducto.categoriaProducto != 1 && mProducto.categoriaProducto != 2 && mProducto.categoriaProducto != 3 && mProducto.categoriaProducto != 4);

                            long pos3 = ftell(ptrArchivo) - sizeof(mProducto);
                            fseek(ptrArchivo, pos3, SEEK_SET);
                            fwrite(&mProducto, sizeof(mProducto), 1, ptrArchivo);
                            system(CLEAR);
                            tituloEncargado();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 5:

                            printf("\n\t\t\t\t\t\tModificar precio de compra\n\n");

                            printf("\n\t\t\t\t\t\tID: %s\n", mProducto.idProducto);

                            printf("\n\t\t\t\t\t\t$ COMPRA: ");
                            scanf("%f%*c", &mProducto.precioCompra);

                            long pos4 = ftell(ptrArchivo) - sizeof(mProducto);
                            fseek(ptrArchivo, pos4, SEEK_SET);
                            fwrite(&mProducto, sizeof(mProducto), 1, ptrArchivo);
                            system(CLEAR);
                            tituloEncargado();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado == 1;

                            break;

                        case 6:

                            printf("\n\t\t\t\t\t\tModificar precio de venta\n\n");

                            printf("\n\t\t\t\t\t\tID: %s\n", mProducto.idProducto);

                            printf("\n\t\t\t\t\t\t$ VENTA: ");
                            scanf("%f%*c", &mProducto.precioVenta);

                            long pos5 = ftell(ptrArchivo) - sizeof(mProducto);
                            fseek(ptrArchivo, pos5, SEEK_SET);
                            fwrite(&mProducto, sizeof(mProducto), 1, ptrArchivo);
                            system(CLEAR);
                            tituloEncargado();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 7:

                            printf("\n\t\t\t\t\t\tModificar numero de existencias\n\n");

                            printf("\n\t\t\t\t\t\tID: %s\n", mProducto.idProducto);

                            printf("\n\t\t\t\t\t\tEXISTENCIAS: ");
                            scanf("%d%*c", &mProducto.existencia);

                            long pos6 = ftell(ptrArchivo) - sizeof(mProducto);
                            fseek(ptrArchivo, pos6, SEEK_SET);
                            fwrite(&mProducto, sizeof(mProducto), 1, ptrArchivo);
                            system(CLEAR);
                            tituloEncargado();
                            printf("\n\t\t\t\t\t\tDatos actualizados correctamente\n\n");

                            encontrar = 1;
                            modificado = 1;

                            break;

                        case 0:
                            menuInventario();

                        default:
                            printf("\n\t\t\t\t\t        La opcion no existe, intentelo de nuevo\n\n");
                            modificado = 0;
                        }
                        if (modificado == 1)
                        {
                            printf("\n\t\t\t\t\t           ==> PRODUCTO MODIFICADO <==\n");
                            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n");
                            printf(" %10s%25s%28s%15s%15s%15s%15s\n", "ID", "PRODUCTO", "MARCA", "CATEGORIA", "$ COMPRA", "$ VENTA", "EXISTENCIA");
                            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

                            printf("   %10s", mProducto.idProducto);
                            printf("%25s", mProducto.nombreProducto);
                            printf("%25s", mProducto.marcaProducto);
                            printf("%15d", mProducto.categoriaProducto);
                            printf("%15.2f", mProducto.precioCompra);
                            printf("%15.2f", mProducto.precioVenta);
                            printf("%15d", mProducto.existencia);
                            printf("\n");

                            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
                        }
                    } while (modificado == 0);
                }

                fread(&mProducto, sizeof(mProducto), 1, ptrArchivo);
            }
        }

        fclose(ptrArchivo);

        if (codigo != mProducto.idProducto && modificado == 0)
        {
            printf(ANSI_COLOR_RED "\t\t\t\t\t\tERROR: El ID ingresado no pertenece a ningun producto\n" ANSI_COLOR_RESET);
            printf(ANSI_COLOR_BLUE "\t\t   -------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
            printf("\n\t\t\t\t\t\tDesea intentarlo de nuevo? [S/N]: ");
            scanf("%s%*c", &respuesta);
        }

        if (modificado == 1)
        {
            printf("\n\t\t\t\t\t      Desea modificar otro producto? [S/N]: ");
            scanf("%s%*c", &respuesta);

            printf("\n");
        }

    } while (respuesta == 'S' || respuesta == 's');
};

// ****************************************FN3 CAPTURA DE VENTAS***************************************

struct registroVentas capturarV()
{

    struct registroVentas registroVen;
    struct registroProductos Producto;

    FILE *ptrArchivo = NULL;

    int repite = 1;
    int ID, nPieza, existeProducto, opcion;
    float preVenta = 0, cambio, recibo, precio;
    char nombreProducto[50], respuesta, regProduct;

    do
    {
        // system(CLEAR);
        tituloAdmin();
        preVenta = 0;

        ptrArchivo = fopen("Inventario1.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t                    ==> PRODUCTOS REGISTRADOS <==\n");
            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n");
            printf(" %10s%25s%28s%15s%15s%15s%15s\n", "ID", "PRODUCTO", "MARCA", "CATEGORIA", "$ COMPRA", "$ VENTA", "EXISTENCIA");
            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&Producto, sizeof(Producto), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {
                printf("   %10s", Producto.idProducto);
                printf("%25s", Producto.nombreProducto);
                printf("%25s", Producto.marcaProducto);
                printf("%15d", Producto.categoriaProducto);
                printf("%15.2f", Producto.precioCompra);
                printf("%15.2f", Producto.precioVenta);
                printf("%15d", Producto.existencia);
                printf("\n");
                fread(&Producto, sizeof(Producto), 1, ptrArchivo);
            }
            printf(ANSI_COLOR_BLUE "   ----------------------------------------------------------------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }

        fclose(ptrArchivo);

        printf("\n\n\t\t\t\t\t\t>> CAPTURAR VENTAS <<\n");
        printf("\t\t\t\t\t\t   ===============\n\n");
        do
        {
            existeProducto = 0;

            ptrArchivo = fopen("Inventario1.dat", "rb");

            if (ptrArchivo != NULL)
            {

                printf("\t\t\t\t\tIntroduce nombre de producto: ");
                scanf(" %[^\n]%*c", nombreProducto);

                fread(&Producto, sizeof(Producto), 1, ptrArchivo);
                while (!feof(ptrArchivo) && existeProducto == 0)
                {
                    if (strcmp(nombreProducto, Producto.nombreProducto) == 0)
                    {
                        existeProducto = 1;
                        precio = Producto.precioVenta;
                    }
                    fread(&Producto, sizeof(Producto), 1, ptrArchivo);
                }

                break;

                fclose(ptrArchivo);
            }

            if (existeProducto == 0)
            {
                printf("\n\t\t\t\t\tEl producto %s no existe.\n\n\n", nombreProducto);
            }

        } while (existeProducto == 0);

        if (existeProducto == 1)
        {
            strcpy(registroVen.producto, nombreProducto);

            printf("\t\t\t\t\tIntroduce cantidad de piezas: ");
            scanf("%d", &nPieza);

            registroVen.cantidad = nPieza;

            printf("\n");

            preVenta += registroVen.cantidad * precio;
        }

        if (existeProducto == 1)
        {

            registroVen.ventaTotal = preVenta;

            printf("\t\t\t\t\tEl total es: %.2f\n", registroVen.ventaTotal);

            printf(" \n");

            printf("\t\t\t\t\t\t\tMETODO DE PAGO\n");
            printf(" \t\t\t\t\t\t\t==============\n\n");
            printf(" \t\t\t\t\t\t        [1]. Efectivo\n");
            printf(" \t\t\t\t\t\t        [2]. Tarjeta\n");
            printf(" \n\n");
            printf("\t\t\t\t\t         Introduce la forma de pago: [ ]\b\b");
            scanf("%d\0", &opcion);
            printf("\n");

            switch (opcion)
            {

            case 1:

                printf("\t\t\t\t\t\tIngresa la cantidad recibida: ");
                scanf("%f%*c", &recibo);

                cambio = recibo - preVenta;

                printf("\t\t\t\t\t\tEl cambio es de: %.2f", cambio);

                break;

            case 2:

                break;

            default:

                printf("\n\t\t\t\t\tEl metodo de pago seleccionado no existe\n\n");
            }
        }

        if (ptrArchivo != NULL || ptrArchivo == NULL)
        {
            ptrArchivo = fopen("Ventas.dat", "ab");
            if (ptrArchivo != NULL)
            {
                fwrite(&registroVen, sizeof(registroVen), 1, ptrArchivo);
                printf("\n\n\t\t\t\t\t\tGracias por su compra\n\n");
            }
            fclose(ptrArchivo);
        }
        else
        {
            printf("\n\n\t\t\t\t\t   Venta no realizada");
        }
        if (ptrArchivo != NULL || ptrArchivo == NULL)
        {

            int enco = 0;
            ptrArchivo = fopen("Inventario1.dat", "r+b");

            if (ptrArchivo != NULL)
            {
                fread(&Producto, sizeof(Producto), 1, ptrArchivo);
                while (!feof(ptrArchivo) && enco == 0)
                {
                    if (strcmp(Producto.nombreProducto, nombreProducto) == 0)
                    {
                        long pos = ftell(ptrArchivo) - sizeof(Producto);
                        fseek(ptrArchivo, pos, SEEK_SET);
                        Producto.existencia = Producto.existencia - nPieza;
                        fwrite(&Producto, sizeof(Producto), 1, ptrArchivo);

                        enco = 1;
                    }
                    fread(&Producto, sizeof(Producto), 1, ptrArchivo);
                }
                fclose(ptrArchivo);
            }
        }
        printf("\n\t\t\t\t\t        Desea realizar otra venta? [S/N]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while ((respuesta == 'S' || respuesta == 's'));
}

// ____________________________________FN18 CONSULTA TODAS LAS VENTAS_________________________________

struct registroVentas consultarVentas()
{

    struct registroVentas consultaVenta;

    FILE *ptrArchivo = NULL;

    int cont = 0;
    char respuesta;

    do
    {
        system(CLEAR);
        tituloEncargado();

        ptrArchivo = fopen("Ventas.dat", "rb");

        if (ptrArchivo != NULL)
        {
            printf("\n\t\t\t\t               ==> VENTAS REGISTRADAS <==\n");
            printf(ANSI_COLOR_YELLOW "\t\t\t ---------------------------------------------------------------------\n");
            printf("\t\t%25s%20s%25s\n", "PRODUCTO", "CANTIDAD", "TOTAL");
            printf(ANSI_COLOR_YELLOW "\t\t\t ---------------------------------------------------------------------\n" ANSI_COLOR_RESET);

            fread(&consultaVenta, sizeof(consultaVenta), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {
                printf("\t\t%25s", consultaVenta.producto);
                printf("%20d", consultaVenta.cantidad);
                printf("%25.2f", consultaVenta.ventaTotal);
                printf("\n");

                cont++;

                fread(&consultaVenta, sizeof(consultaVenta), 1, ptrArchivo);
            }
            if (cont == 0)
            {
                printf("\t\t   No existen ventas registradas\n\n");
            }
            printf(ANSI_COLOR_YELLOW "\t\t\t ---------------------------------------------------------------------\n" ANSI_COLOR_RESET);
        }

        fclose(ptrArchivo);

        printf("\n\t\t\t\t   Preciona 'S' para salir o 'A' para actualizar? [S/A]: ");
        scanf("%s%*c", &respuesta);

        printf("\n");

    } while (respuesta == 'A' || respuesta == 'a');
};

// ***********************************************LOGIN****************************************************

struct registroUsuario login()
{

    struct registroUsuario inicioSesion;

    FILE *ptrArchivo = NULL;

    system(CLEAR);
    tituloLogin();

    int existe, existeUser = 0, existeAdmin = 0, intentos = 1;
    char nombreUsuario[50], contrasena[50];

    do
    {
        printf("\n");
        printf("\t\t\t\t\t\t\tINICIAR SESION\n");
        printf("\t\t\t\t\t\t\t==============\n\n");

        printf("\t\t\t\t\t\t     USUARIO: ");
        scanf("%s%*c", nombreUsuario);

        printf("\t\t\t\t\t\t     PASSWORD: ");
        scanf("%s%*c", contrasena);

        if (strcmp(nombreUsuario, USER) == 0 && strcmp(contrasena, PASS) == 0)
        {
            existeAdmin = 1;
        }

        if (existeAdmin == 1)
        {
            if (ptrArchivo != NULL || ptrArchivo == NULL)
            {
                ptrArchivo = fopen("Sesion.dat", "ab");
                if (ptrArchivo != NULL)
                {
                    fwrite(&inicioSesion, sizeof(inicioSesion), 1, ptrArchivo);
                    printf("\n\n\t\t\t\t\t        Usuario creado correctamente\n\n");
                }
                fclose(ptrArchivo);
            }
            menuAdmin();
        }

        ptrArchivo = fopen("Usuarios.dat", "rb");

        if (ptrArchivo != NULL)
        {
            fread(&inicioSesion, sizeof(inicioSesion), 1, ptrArchivo);
            while (!feof(ptrArchivo))
            {
                if (strcmp(inicioSesion.usuario, nombreUsuario) == 0 && strcmp(inicioSesion.password, contrasena) == 0)
                {
                    existeUser = 1;
                    break;
                }
                fread(&inicioSesion, sizeof(inicioSesion), 1, ptrArchivo);
            }
            fclose(ptrArchivo);
        }

        if (existeUser == 1)
        {
            if (ptrArchivo != NULL || ptrArchivo == NULL)
            {
                ptrArchivo = fopen("Sesion.dat", "ab");
                if (ptrArchivo != NULL)
                {
                    fwrite(&inicioSesion, sizeof(inicioSesion), 1, ptrArchivo);
                    printf("\n\n\t\t\t\t\t        Usuario creado correctamente\n\n");
                }
                fclose(ptrArchivo);
            }
            menuInventario();
        }

        if (existeAdmin == 0 || existeUser == 0)
        {
            if (intentos < 3)
            {
                existe = 0;
                system(CLEAR);
                tituloLogin();
                printf("\n\t\t\t\t   El usuario o password son incorrectos. Intentelo de nuevo\n");
            }
        }

        intentos++;

    } while (existe == 0 && intentos <= 3);

    if (intentos > 3)
    {
        system(CLEAR);
        tituloLogin();
        printf("\n\t\t\t\t\tHas excedido la cantidad de intentos permitidos\n\n");
        exit(-1);
    }
}

// ********************************************MENU ADMINISTRADOR*******************************************

int menuAdmin()
{

    int opcion, seguir = 1, opcInventario;

    system(CLEAR);
    tituloAdmin();

    do
    {
        printf(" \n");

        printf("\t\t\t\t\t\t\tMENU ADMINISTRADOR\n");
        printf(" \t\t\t\t\t\t\t==================\n\n");
        printf(" \t\t\t\t\t\t   [1]. Ingresar a los usuarios\n");
        printf(" \t\t\t\t\t\t   [2]. Ingresar al inventario\n");
        printf(" \t\t\t\t\t\t   [3]. Ingresar a las sucursales\n");
        printf(" \t\t\t\t\t\t   [0]. Cerrar Sesion\n");
        printf(" \n\n");
        printf("\t\t\t\t\t    Introduce la opcion que deseas ejecutar: [ ]\b\b");
        scanf("%d%*c\0", &opcion);

        printf("\n");

        switch (opcion)
        {

        case 1:

            menuUsuario();

            break;

        case 2:

            menuInventario();

            break;

        case 3:

            menuSucursal();

            break;

        case 0:
            seguir = 0;
            remove("Sesion.dat");
            login();

            break;

        default:
            printf("\n\t\tLa opcion seleccionada no existe\n\n");
        }

    } while (seguir == 1);
}

// ***********************************************MENU USUARIOS**********************************************

int menuUsuario()
{

    int opcion, seguir = 1;

    system(CLEAR);

    do
    {
        tituloAdmin();
        printf(" \n");

        printf("\t\t\t\t\t\t\tMENU DE USUARIOS\n");
        printf("\t\t\t\t\t\t\t================\n\n");
        printf(" \t\t\t\t\t\t   [1]. Registrar usuario\n");
        printf(" \t\t\t\t\t\t   [2]. Eliminar usuario\n");
        printf(" \t\t\t\t\t\t   [3]. Modificar  usuario\n");
        printf(" \t\t\t\t\t\t   [4]. Consultar un usuario\n");
        printf(" \t\t\t\t\t\t   [5]. Consultar todos los usuarios\n");
        printf(" \t\t\t\t\t\t   [0]. Volver\n");
        printf(" \n\n");
        printf("\t\t\t\t\t     Introduce la opcion que deseas ejecutar: [ ]\b\b");
        scanf("%d\0", &opcion);

        printf("\n");

        switch (opcion)
        {

        case 1:

            capturar();

            break;

        case 2:

            eliminarU();

            break;

        case 3:

            modificarU();

            break;

        case 4:

            consultarU();

            break;

        case 5:

            consultarTodosUsuarios();

            break;

        case 0:
            menuAdmin();

            break;

        default:

            printf("\nLa opcion seleccionada no existe");
        }

    } while (seguir = 1);
}

// ***********************************************MENU INVENTARIO**********************************************

int menuInventario()
{
    int opcion, seguir = 1;

    system(CLEAR);

    do
    {
        tituloEncargado();
        printf(" \n");

        printf("\t\t\t\t\t\t\tMENU DE INVENTARIO\n");
        printf("\t\t\t\t\t\t\t==================\n\n");
        printf(" \t\t\t\t\t\t   [1]. Registrar producto\n");
        printf(" \t\t\t\t\t\t   [2]. Eliminar producto\n");
        printf(" \t\t\t\t\t\t   [3]. Modificar  producto\n");
        printf(" \t\t\t\t\t\t   [4]. Consultar productos por categoria\n");
        printf(" \t\t\t\t\t\t   [5]. Consultar todos los productos\n");
        printf(" \t\t\t\t\t\t   [6]. Capturar ventas\n");
        printf(" \t\t\t\t\t\t   [7]. Consultar ventas\n");
        printf(" \t\t\t\t\t\t   [8]. Consultar productos en otra sucursal\n");
        printf(" \t\t\t\t\t\t   [0]. Cerrar Sesion\n");
        printf(" \n\n");
        printf("\t\t\t\t\t     Introduce la opcion que deseas ejecutar: [ ]\b\b");
        scanf("%d%*c\0", &opcion);

        printf("\n");

        switch (opcion)
        {

        case 1:

            capturarP1();

            break;

        case 2:

            eliminarP();

            break;

        case 3:

            modificarP();

            break;

        case 4:

            consultarProductosCategoria();

            break;

        case 5:

            consultarTodosProductos();

            break;

        case 6:

            capturarV();

            break;

        case 7:

            consultarVentas();

            break;

        case 8:

            consultaEnSucursal();

            break;

        case 0:

            remove("Sesion.dat");
            login();

            break;

        default:

            printf("\nLa opcion seleccionada no existe");
        }

    } while (seguir = 1);
}

// ***********************************************MENU SUCURSALES**********************************************

int menuSucursal()
{

    int opcion, seguir = 1;

    system(CLEAR);

    do
    {
        tituloAdmin();
        printf(" \n");

        printf("\t\t\t\t\t\t\tMENU DE SUCURSALES\n");
        printf("\t\t\t\t\t\t\t==================\n\n");
        printf(" \t\t\t\t\t\t   [1]. Registrar Sucursal\n");
        printf(" \t\t\t\t\t\t   [2]. Eliminar Sucursal\n");
        printf(" \t\t\t\t\t\t   [3]. Modificar sucursal\n");
        printf(" \t\t\t\t\t\t   [4]. Consultar una sucursal\n");
        printf(" \t\t\t\t\t\t   [5]. Consultar todas las sucursales\n");
        printf(" \t\t\t\t\t\t   [0]. Volver\n");
        printf(" \n\n");
        printf("\t\t\t\t\t    Introduce la opcion que deseas ejecutar: [ ]\b\b");
        scanf("%d\0", &opcion);

        printf("\n");

        switch (opcion)
        {

        case 1:

            capturarS();

            break;

        case 2:

            eliminarS();

            break;

        case 3:

            modificarS();

            break;

        case 4:

            consultarS();

            break;

        case 5:

            consultarTodasSucursales();

            break;

        case 0:
            menuAdmin();

            break;

        default:

            printf("\nLa opcion seleccionada no existe");
        }

    } while (seguir = 1);
}

// ***********************************************TITULO ADMIN**********************************************

void tituloAdmin()
{
    system(CLEAR);

    printf("\n\t\t\t     ======================================================================\n");
    printf("\t\t\t\t\t\t  OPERACIONES DE ADMINISTRADOR\n");
    printf("\t\t\t\t     Creacion, eliminacion, actualizacion y busquedas de\n");
    printf("\t\t\t\t\t       USUARIOS, SUCURSALES E INVENTARIO\n");
    printf("\t\t\t\t\t          Copyright 2021 | Estancia 1\n");
    printf("\t\t\t     ======================================================================\n\n\n");

    printf("_________________________________________________________________________________________________________________________________\n");
}

// ***********************************************TITULO ENCARGADO**********************************************

void tituloEncargado()
{
    system(CLEAR);

    printf("\n\t\t\t     ======================================================================\n");
    printf("\t\t\t\t\t\t  OPERACIONES DE ENCARGADO\n");
    printf("\t\t\t\t     Creacion, eliminacion, actualizacion y busquedas de\n");
    printf("\t\t\t\t\t\t\t INVENTARIO\n");
    printf("\t\t\t\t\t         Copyright 2021 | Estancia 1\n");
    printf("\t\t\t     ======================================================================\n\n\n");

    printf("_________________________________________________________________________________________________________________________________\n");
}

// ***********************************************TITULO ENCARGADO**********************************************

void tituloLogin()
{

    printf("\n\t\t    =====================================================================================\n");
    printf("\t\t\t  SISTEMA DE GESTION DE VENTAS E INVENTARIO PARA UNA EMPRESA DE COSMETICOS\n");
    printf("\t\t\t\t     Creacion, eliminacion, actualizacion y busquedas de\n");
    printf("\t\t\t\t\t       USUARIOS, SUCURSALES E INVENTARIO\n");
    printf("\t\t\t\t\t         Copyright 2021 | Estancia 1\n");
    printf("\t\t    =====================================================================================\n\n\n");

    printf("_________________________________________________________________________________________________________________________________\n");
}

// *****************************************************MAIN************************************************

int main()
{
    login();
}
